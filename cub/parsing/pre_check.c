/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:51 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/23 00:03:11 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_extension(const char *path, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(path) - 5;
	j = -1;
	if (i <= 0)
		return (EXIT_F);
	while (path[i])
		if (!(ext[++j] == path[++i]))
			return (EXIT_F);
	return (EXIT_S);
}

static int	check_rgb(const char *line)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), EXIT_F);
	if (!rgb[0][0] || !rgb[1][0] || !rgb[2][0])
		return (free_split(rgb), EXIT_F);
	if ((ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255)
		|| (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255)
		|| (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255))
		return (free_split(rgb), EXIT_F);
	return (free_split(rgb), EXIT_S);
}

static int	check_texture_line(char *line, char *config)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
		return (free_split(tokens), EXIT_F);
	if (ft_strcmp(tokens[0], config) != 0)
		return (free_split(tokens), EXIT_F);
	if (check_extension(tokens[1], ".xpm"))
		return (free_split(tokens), EXIT_F);
	free_split(tokens);
	return (EXIT_S);
}

static int	check_color_line(char *line, char *config)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
		return (free_split(tokens), EXIT_F);
	if (ft_strcmp(tokens[0], config) != 0)
		return (free_split(tokens), EXIT_F);
	if (check_rgb(tokens[1]))
		return (free_split(tokens), EXIT_F);
	free_split(tokens);
	return (EXIT_S);
}

int	check_structure(char **lines, int lcount)
{
	if (check_texture_line(lines[0], "NO")
		|| check_texture_line(lines[1], "SO")
		|| check_texture_line(lines[2], "WE")
		|| check_texture_line(lines[3], "EA"))
		return (error_msg("Error\nInvalid texture config.", EXIT_F));
	if (lines[4][0] != '\0')
		return (error_msg("Error\nExpected empty line after textures.",
				EXIT_F));
	if (check_color_line(lines[5], "F")
		|| check_color_line(lines[6], "C"))
		return (error_msg("Error\nInvalid texture config.", EXIT_F));
	if (lines[7][0] != '\0')
		return (error_msg("Error\nExpected empty line after textures.",
				EXIT_F));
	if (find_map_start(lines, lcount) != 8)
		return (error_msg("Error\nLines a lot before map.", EXIT_F));
	return (EXIT_S);
}
