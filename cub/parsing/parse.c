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
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

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

static int	validate_rgb(t_color *c)
{
	if ((c->r < 0 || c->r > 255)
		|| (c->g < 0 || c->g > 255)
		|| (c->b < 0 || c->b > 255))
		return (error_msg("Error\nRGB out of range (0-255).",
				EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	parse_cor(char *line, t_color *c)
{
	char	**rgb;

	if (!line || !c)
		return (error_msg("Error\nColor parsing failed.",
				EXIT_FAILURE));
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (error_msg("Error\nInvalid color format.",
				EXIT_FAILURE));
	c->r = ft_atoi(rgb[0]);
	c->g = ft_atoi(rgb[1]);
	c->b = ft_atoi(rgb[2]);
	free_split(rgb);
	return (validate_rgb(c));
}

static char	*parse_texture(char *line)
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
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	line_color(char **tokens, t_config *c)
{
	if (!ft_strcmp(tokens[0], "F"))
		return (parse_cor(tokens[1], &c->chao));
	else if (!ft_strcmp(tokens[0], "C"))
		return (parse_cor(tokens[1], &c->teto));
	return (EXIT_FAILURE);
}

int	parse_line(char *line, t_config *c)
{
	char	**tokens;
	int		ret;

	ret = EXIT_SUCCESS;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (error_msg("Error\nInvalid c line.",
				EXIT_FAILURE));
	if (line_texture(tokens, c) && line_color(tokens, c))
		ret = error_msg("Error\nDuplicate or invalid "
				"identifier in .cub.", EXIT_FAILURE);
	free_split(tokens);
	return (ret);
}

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

char	**read_all_lines(int fd, int *count)
{
	char	**lines;
	char	*line;
	char	**tmp;

	lines = NULL;
	*count = 0;
	while (line = ft_strtrim(get_next_line(fd), "\n"))
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
		return (error_msg("Error\nInvalid args in open_cub.", EXIT_FAILURE));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("Error\nFailed to open .cub file.", EXIT_FAILURE));
	lines = read_all_lines(fd, &lcount);
	close(fd);
	if (!lines)
		return (error_msg("Error\nReading .cub failed.", EXIT_FAILURE));
	start_map = find_map_start(lines, lcount);
	if (start_map == -1)
		return (free_lines(lines, lcount),
			error_msg("Error\nNo map found in .cub.", EXIT_FAILURE));
	if (parse_config(lines, start_map, &g->config)
		|| parse_map(lines, start_map, &g->map, &g->player)
		|| validar_mapa(&g->map, &g->player))
		return (free_lines(lines, lcount), EXIT_FAILURE);
	return (free_lines(lines, lcount), EXIT_SUCCESS);
}
