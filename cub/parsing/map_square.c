/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:04:48 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:04:49 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	fill_square_line(t_map *map, int x, int len)
{
	char	*new_line;
	int		i;

	new_line = (char *)malloc(sizeof(char) * (map->width + 1));
	if (!new_line)
		return (error_msg("Error\nFalied to malloc in square_mape.",
				EXIT_F));
	i = -1;
	while (++i < len)
		new_line[i] = map->grade[x][i];
	while (i < map->width)
		new_line[i++] = ' ';
	new_line[i] = '\0';
	free(map->grade[x]);
	map->grade[x] = new_line;
	return (EXIT_S);
}

static int	square_map(t_map *map)
{
	int	i;
	int	len;

	i = -1;
	while (++i < map->height)
	{
		len = ft_strlen(map->grade[i]);
		if (len < map->width)
			if (fill_square_line(map, i, len))
				return (EXIT_F);
	}
	return (EXIT_S);
}

static int	surrounded_check(t_map *map, int i, int j)
{
	if (i == 0 || j == 0 || i == (map->height - 1) || j == (map->width - 1))
		return (0);
	if (map->grade[i - 1][j] == ' ' || map->grade[i + 1][j] == ' ' ||
		map->grade[i][j - 1] == ' ' || map->grade[i][j + 1] == ' ')
		return (0);
	return (1);
}

static int	check_cell(t_map *map, t_player *p, int i, int j)
{
	char	c;

	c = map->grade[i][j];
	if ((c != '\0') && !is_valid_char(c))
		return (error_msg("Error\nInvalid char on the map.",
				EXIT_F));
	if (c == '0' || (i == p->y && j == p->x))
		if (!surrounded_check(map, i, j))
			return (error_msg("Error\nOpen space or adjacent"
					"space detected.", EXIT_F));
	return (EXIT_S);
}

int	validate_map(t_map *map, t_player *player)
{
	int		i;
	int		j;

	i = -1;
	(void)player;
	if (square_map(map))
		return (error_msg("Error\nFailure to normalize the map.",
				EXIT_F));
	while (++i < map->height)
	{
		j = -1;
		while (map->grade[i][++j])
			if (check_cell(map, player, i, j))
				return (EXIT_F);
	}
	return (EXIT_S);
}
