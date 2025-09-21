#include "../cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_values(t_player *p, double dx, double dy, double px, double py)
{
	p->dx = dx;
	p->dy = dy;
	p->px = px;
	p->py = py;
}

int	set_direction(t_player *player)
{
	if (!player || !player->direction)
		return (error_msg("Error\nRealloc failure.", EXIT_F));
	if (player->direction == 'N')
		set_values(player, 0, -1, 0.66, 0);
	else if (player->direction == 'S')
		set_values(player, 0, 1, -0.66, 0);
	else if (player->direction == 'E')
		set_values(player, 1, 0, 0, 0.66);
	else if (player->direction == 'W')
		set_values(player, -1, 0, 0, -0.66);
	return (EXIT_S);
}

static int	set_player(t_player *player, int x, int y, char dir)
{
	if (player->direction)
		return (error_msg("Error\nThere is more than one player on the map.",
				EXIT_F));
	player->x = x;
	player->y = y;
	player->direction = dir;
	if (set_direction(player))
		return (error_msg("Error\nFailed to set direction.", EXIT_F));
	return (EXIT_S);
}

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

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

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
