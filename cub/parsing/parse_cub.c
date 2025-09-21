#include "../cub3d.h"

static int is_player(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void set_values(t_player *p, double dx, double dy, double px, double py)
{
    p->dx = dx;
    p->dy = dy;
    p->px = px;
    p->py = py;
}

int set_direction(t_player *player)
{
    if (!player || !player->direction)
        return (error_msg("Error\nRealloc failure.", EXIT_FAILURE));
    if (player->direction == 'N')
        set_values(player, 0, -1, 0.66, 0);
    else if (player->direction == 'S')
        set_values(player, 0, 1, -0.66, 0);
    else if (player->direction == 'E')
        set_values(player, 1, 0, 0, 0.66);
    else if (player->direction == 'W')
        set_values(player, -1, 0, 0, -0.66);
    return (EXIT_SUCCESS);
}

static int set_player(t_player *player, int x, int y, char dir)
{
    if (player->direction)
        return (error_msg("Error\nThere is more than one player on the map.", EXIT_FAILURE));
    player->x = x;
    player->y = y;
    player->direction = dir;
    if (set_direction(player))
        return (error_msg("Error\nFailed to set direction.", EXIT_FAILURE));
    return (EXIT_SUCCESS);
}

static int map_hlen(char **lines, int start)
{
    int h;

    h = 0;
    while (lines[start + h] && lines[start + h][0] != '\n')
        h++;
    return (h);
}

char    *lines_strdup(const char *s)
{
    size_t     len;
    char    *dup;

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

int parse_map(char **lines, int start, t_map *map, t_player *player)
{
    int i;
    int j;

    map->height = map_hlen(lines, start);
    map->grade = malloc(sizeof(char *) * (map->height + 1));
    if (!map->grade)
        return (error_msg("Error\nFalied in malloc.", EXIT_FAILURE));
    i = -1;
    while (++i < map->height)
    {
        map->grade[i] = lines_strdup(lines[start + i]);
        if (!map->grade[i])
            return (error_msg("Error\nFailed to duplicate map line.", EXIT_FAILURE));
        if ((int)ft_strlen(map->grade[i]) > map->width)
            map->width = ft_strlen(map->grade[i]);
        j = -1;
        while (map->grade[i][++j])
        {
            if (is_player(map->grade[i][j]))
            {
                if (set_player(player, j, i, map->grade[i][j]))
                    return (EXIT_FAILURE);
                map->grade[i][j] = '0';
            }
        }
    }
    map->grade[i] = NULL;
    if (!player->direction)
        return (error_msg("Error\nMap without player to game.", EXIT_FAILURE));
    return (EXIT_SUCCESS);
}

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' ||
            c == 'N' || c == 'S' || c ==  'E' || c == 'W');
}

static int square_map(t_map *map)
{
    int i;
    int j;
    int len;
    char *new_line;

    i = -1;
    while (++i < map->height)
    {
        len = ft_strlen(map->grade[i]);
        if (len < map->width)
        {
            new_line = (char *)malloc(sizeof(char) * (map->width + 1));
            if (!new_line)
                return (error_msg("Error\nFalied to malloc in square_mape.", EXIT_FAILURE));
            j = -1;
            while (++j < len)
                new_line[j] = map->grade[i][j];
            while (j < map->width)
                new_line[j++] = ' ';
            new_line[j] = '\0';
            free(map->grade[i]);
            map->grade[i] = new_line;
        }
    }
    return (EXIT_SUCCESS);
}

static int surrounded_check(t_map *map, int i, int j)
{
    if (i == 0 || j == 0 || i == (map->height - 1) || j == (map->width - 1))
        return (0);
    if (map->grade[i - 1][j] == ' ' || map->grade[i + 1][j] == ' ' ||
        map->grade[i][j - 1] == ' ' || map->grade[i][j + 1] == ' ')
        return (0);
    return (1);
}

int validar_mapa(t_map *map, t_player *player)
{
    int i;
    int j;
    char c;

    i = -1;
    (void)player;
    if (square_map(map))
        return (error_msg("Error\nFailure to normalize the map.", EXIT_FAILURE));
    while (++i < map->height)
    {
        j = -1;
        while (map->grade[i][++j])
        {
            c = map->grade[i][j];
            if ((c != '\0') && !is_valid_char(c))
                return (error_msg("Error\nInvalid char on the map.", EXIT_FAILURE));

            if (c == '0' || (i == player->y && j == player->x))
            {
                if (!surrounded_check(map, i, j))
                    return (error_msg("Error\nOpen space or adjacent space detected.", EXIT_FAILURE));
            }
        }
    }
    return (EXIT_SUCCESS);
}