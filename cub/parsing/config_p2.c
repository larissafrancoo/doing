/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:04:20 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:04:23 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_split(char **s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

int	is_config_line(char *line)
{
	char	**tokens;
	int		ret;

	if (!line || !*line)
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	ret = (tokens[0]
			&& (!ft_strcmp(tokens[0], "NO")
				|| !ft_strcmp(tokens[0], "SO")
				|| !ft_strcmp(tokens[0], "WE")
				|| !ft_strcmp(tokens[0], "EA")
				|| !ft_strcmp(tokens[0], "F")
				|| !ft_strcmp(tokens[0], "C")));
	free_split(tokens);
	return (ret);
}

static int	line_texture(char **tokens, t_config *c)
{
	if (!ft_strcmp(tokens[0], "NO") && !c->tex.no)
		c->tex.no = parse_texture(tokens[1]);
	else if (!ft_strcmp(tokens[0], "SO") && !c->tex.so)
		c->tex.so = parse_texture(tokens[1]);
	else if (!ft_strcmp(tokens[0], "WE") && !c->tex.we)
		c->tex.we = parse_texture(tokens[1]);
	else if (!ft_strcmp(tokens[0], "EA") && !c->tex.ea)
		c->tex.ea = parse_texture(tokens[1]);
	else
		return (EXIT_F);
	return (EXIT_S);
}

static int	line_color(char **tokens, t_config *c)
{
	if (!ft_strcmp(tokens[0], "F"))
		return (parse_color(tokens[1], &c->floor));
	else if (!ft_strcmp(tokens[0], "C"))
		return (parse_color(tokens[1], &c->cell));
	return (EXIT_F);
}

int	parse_line(char *line, t_config *c)
{
	char	**tokens;
	int		ret;

	ret = EXIT_S;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (error_msg("Error\nInvalid c line.",
				EXIT_F));
	if (line_texture(tokens, c) && line_color(tokens, c))
		ret = error_msg("Error\nDuplicate or invalid "
				"identifier in .cub.", EXIT_F);
	free_split(tokens);
	return (ret);
}
