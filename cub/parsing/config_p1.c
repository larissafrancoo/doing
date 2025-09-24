/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_p1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:04:11 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/23 00:00:33 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_config(char **lines, int start_map, t_config *config)
{
	int	i;

	i = -1;
	while (++i < start_map)
	{
		if (lines[i][0] && is_config_line(lines[i]))
		{
			if (parse_line(lines[i], config))
				return (EXIT_F);
		}
	}
	return (EXIT_S);
}

static int	validate_rgb(t_color *c)
{
	if ((c->r < 0 || c->r > 255)
		|| (c->g < 0 || c->g > 255)
		|| (c->b < 0 || c->b > 255))
		return (error_msg("Error\nRGB out of range (0-255).",
				EXIT_F));
	return (EXIT_S);
}

int	parse_color(char *line, t_color *c)
{
	char	**rgb;

	if (!line || !c)
		return (error_msg("Error\nColor parsing failed.",
				EXIT_F));
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb),
			error_msg("Error\nInvalid color format.",
				EXIT_F));
	c->r = ft_atoi(rgb[0]);
	c->g = ft_atoi(rgb[1]);
	c->b = ft_atoi(rgb[2]);
	free_split(rgb);
	return (validate_rgb(c));
}

char	*parse_texture(char *line)
{
	char	*path;

	if (!line)
	{
		perror("Error\nInvalid line.");
		return (NULL);
	}
	path = ft_strtrim(line, "\n");
	if (!path)
	{
		perror("Error\nMalloc failed parsing texture.");
		return (NULL);
	}
	return (path);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
