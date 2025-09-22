/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:04:41 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:04:43 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	map_hlen(char **lines, int start)
{
	int	h;

	h = 0;
	while (lines[start + h] && lines[start + h][0] != '\n')
		h++;
	return (h);
}

char	*lines_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = (strlen(s));
	if (len && s[len - 1] == '\n')
		len--;
	dup = (char *) malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

static int	check_map_players(char *line, int x, t_player *p)
{
	int	y;

	y = -1;
	while (line[++y])
	{
		if (is_player(line[y]))
		{
			if (set_player(p, y, x, line[y]))
				return (EXIT_F);
			line[y] = '0';
		}
	}
	return (EXIT_S);
}

static int	parse_map_line(t_map *map, char *s, int x, t_player *p)
{
	map->grade[x] = lines_strdup(s);
	if (!map->grade[x])
		return (error_msg("Error\nFailed to duplicate map line.",
				EXIT_F));
	if ((int)ft_strlen(map->grade[x]) > map->width)
		map->width = ft_strlen(map->grade[x]);
	if (check_map_players(map->grade[x], x, p))
		return (EXIT_F);
	return (EXIT_S);
}

int	parse_map(char **lines, int start, t_map *map, t_player *p)
{
	int	i;
	int	j;

	map->height = map_hlen(lines, start);
	map->grade = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grade)
		return (error_msg("Error\nFalied in malloc.", EXIT_F));
	i = -1;
	while (++i < map->height)
		if (parse_map_line(map, lines[start + i], i, p))
			return (EXIT_F);
	map->grade[i] = NULL;
	if (!p->direction)
		return (error_msg("Error\nMap without player to game.", EXIT_F));
	return (EXIT_S);
}
