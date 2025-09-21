#include "cub3d.h"

int can_move_to(t_game *g, double nx, double ny)
{
    int mx = (int) nx;
    int my = (int) ny;

    if (my < 0 || my >= g->map.height) return 0;
    if (mx < 0 || mx >= g->map.width) return 0;

    if (!g->map.grade[my] || (int)strlen(g->map.grade[my]) <= mx) return 0;

    return (g->map.grade[my][mx] != '1' && g->map.grade[my][mx] != ' ');
}

void rotate_player(t_player *p, double angle)
{
    double old_dx = p->dx;
    double old_px = p->px;

    p->dx = p->dx * cos(angle) - p->dy * sin(angle);
    p->dy = old_dx * sin(angle) + p->dy * cos(angle);

    p->px = p->px * cos(angle) - p->py * sin(angle);
    p->py = old_px * sin(angle) + p->py * cos(angle);
}

static void try_move(t_game *g, double vx, double vy)
{
    double nx = g->player.x + vx;
    double ny = g->player.y + vy;

    if (can_move_to(g, nx, g->player.y))
        g->player.x = nx;
    if (can_move_to(g, g->player.x, ny))
        g->player.y = ny;
}

int handle_key(int keycode, t_game *g)
{
    if (keycode == KEY_ESC)
        return close_game(g);
    
    if (keycode == KEY_W)
        try_move(g, g->player.dx * MOVE_SPEED, g->player.dy * MOVE_SPEED);
    else if (keycode == KEY_S)
        try_move(g, -g->player.dx * MOVE_SPEED, -g->player.dy * MOVE_SPEED);
    else if (keycode == KEY_D)
        try_move(g, -g->player.dy * MOVE_SPEED, g->player.dx * MOVE_SPEED);
    else if (keycode == KEY_A)
        try_move(g, g->player.dy * MOVE_SPEED, -g->player.dx * MOVE_SPEED);
    else if (keycode == KEY_LEFT)
        rotate_player(&g->player, -ROT_SPEED);
    else if (keycode == KEY_RIGHT)
        rotate_player(&g->player, ROT_SPEED);
    
    render_frame(g);
    // //[DEBUG] temporario:
    // printf("Pos: (%.2f, %.2f) Dir: (%.2f, %.2f)\n", g->player.x, g->player.y, g->player.dx, g->player.dy);
    return (0);
}