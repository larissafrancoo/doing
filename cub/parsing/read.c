/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:05:01 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:05:03 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_lines(char **lines, int count)
{
	int	i;

	i = -1;
	if (!lines)
		return ;
	while (++i < count)
		free(lines[i]);
	free(lines);
}

static void	copy_lines(char **dst, char **src, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		dst[i] = src[i];
}

char	gnl_trimmed(int fd, char **line)
{
	char	*tmp;

	if (!line)
		return (0);
	tmp = get_next_line(fd);
	if (!tmp)
	{
		*line = NULL;
		return (0);
	}
	*line = ft_strtrim(tmp, "\n");
	free (tmp);
	if (!*line)
		return (0);
	return (1);
}

char	**read_all_lines(int fd, int *count)
{
	char	**lines;
	char	*line;
	char	**tmp;

	lines = NULL;
	*count = 0;
	while (gnl_trimmed(fd, &line))
	{
		tmp = malloc(sizeof(char *) * (*count + 2));
		if (!tmp)
			return (free_lines(lines, *count), NULL);
		copy_lines(tmp, lines, *count);
		free(lines);
		tmp[*count] = line;
		tmp[*count + 1] = NULL;
		lines = tmp;
		(*count)++;
	}
	return (lines);
}

int	open_cub(t_game *g, const char *path)
{
	int		fd;
	char	**lines;
	int		lcount;
	int		start_map;

	if (!g || !path)
		return (error_msg("Error\nInvalid args in open_cub.", EXIT_F));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("Error\nFailed to open .cub file.", EXIT_F));
	lines = read_all_lines(fd, &lcount);
	close(fd);
	if (!lines)
		return (error_msg("Error\nReading .cub failed.", EXIT_F));
	start_map = find_map_start(lines, lcount);
	if (start_map == -1)
		return (free_lines(lines, lcount),
			error_msg("Error\nNo map found in .cub.", EXIT_F));
	if (parse_config(lines, start_map, &g->config)
		|| parse_map(lines, start_map, &g->map, &g->player)
		|| validate_map(&g->map, &g->player))
		return (free_lines(lines, lcount), EXIT_F);
	return (free_lines(lines, lcount), EXIT_S);
}
