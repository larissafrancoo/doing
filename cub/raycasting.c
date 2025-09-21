#include "cub3d.h"

void my_mlx_pixel_put(t_infos *dado, int x, int y, int color) //podemos transformar essa função no tipo int para que possa retornar em caso de erro.
{
    char *dst;

    if (!dado || !dado->addr)
        return ;
    if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
        return ;
    dst = dado->addr + (y * dado->line_len + x * (dado->bpp / 8));
    *(unsigned int *)dst = color;
}

void desenha_linha_vert(t_game *g, int x, int start, int end, int cor)
{
    int y;
    y = start;

    while (y <= end)
    {
        my_mlx_pixel_put(&g->img, x, y, cor);
        y++;
    }
}

int rgb_to_int(t_color c)
{
    return ((c.r << 16) | (c.g << 8) | c.b);
}

int prepara_frame(t_game *g)
{
    if (g->img.img)
        mlx_destroy_image(g->mlx, g->img.img);
    g->img.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
    if (!g->img.img)
        return (error_msg("Error\n[prepara_frame] Falha ao criar nova imgaem.", EXIT_FAILURE));
    g->img.addr = mlx_get_data_addr(g->img.img,
        &g->img.bpp, &g->img.line_len, &g->img.endian);
    if (!g->img.addr)
        return (error_msg("Error\n[prepara_frame] Falha ao pegar addr da imgaem.", EXIT_FAILURE));
    return (EXIT_SUCCESS);
}

void limpa_bkg(t_game *g)
{
    int x;
    int y;
    int c;
    int t;

    c = rgb_to_int(g->config.chao);
    t = rgb_to_int(g->config.teto);
    y = -1;
    while (++y < WIN_H/2)
    {
        x = -1;
        while (++x < WIN_W)
            my_mlx_pixel_put(&g->img, x, y, t);
    }
    y = WIN_H/2 - 1;
    while (++y < WIN_H)
    {
        x = -1;
        while (++x < WIN_W)
            my_mlx_pixel_put(&g->img, x, y, c);
    }
}

void calc_direction(t_game *g, int x, t_raio *r)
{
    r->cameraX = 2 * x / (double)WIN_W - 1;
    r->rayDirX = g->player.dx + g->player.px * r->cameraX;
    r->rayDirY = g->player.dy + g->player.py * r->cameraX;

    r->mapX = (int)g->player.x;
    r->mapY = (int)g->player.y;
}

void calc_delta(t_raio *r)
{
    if (r->rayDirX == 0)
        r->deltaDistX = 1e30;
    else
        r->deltaDistX = fabs(1 / r->rayDirX);
    
    if (r->rayDirY == 0)
        r->deltaDistY = 1e30;
    else
        r->deltaDistY = fabs(1 / r->rayDirY);
}

void calc_passos(t_game *g, t_raio *r)
{
    r->stepX = 1;
    r->stepY = 1;
    if (r->rayDirX < 0)
    {
        r->stepX = -1;
        r->sideDistX = (g->player.x - r->mapX) * r->deltaDistX;
    }
    else
        r->sideDistX = (r->mapX + 1.0 - g->player.x) * r->deltaDistX;
    
    if (r->rayDirY < 0)
    {
        r->stepY = -1;
        r->sideDistY = (g->player.y - r->mapY) * r->deltaDistY;
    }
    else
        r->sideDistY = (r->mapY + 1.0 - g->player.y) * r->deltaDistY;
}

void inicializar_raio(t_game *g, int x, t_raio *r)
{
    calc_direction(g, x, r);
    calc_delta(r);
    calc_passos(g, r);
    r->hit = 0;
}

void dar_passo(t_raio *r)
{
    if (r->sideDistX < r->sideDistY)
    {
        r->sideDistX += r->deltaDistX;
        r->mapX += r->stepX;
        r->side = 0;
    }
    else
    {
        r->sideDistY += r->deltaDistY;
        r->mapY += r->stepY;
        r->side = 1;
    }
}

void exec_dda(t_game *g, t_raio *r)
{
    int max_steps = 1000;
    while (!r->hit && max_steps--)
    {
        dar_passo(r);
        if (g->map.grade[r->mapY][r->mapX] == '1')
            r->hit = 1;
    }
    if (!r->hit)
        r->perpWallDist = 1000.0;
    if (r->side == 0)
        r->perpWallDist = (r->mapX - g->player.x + (1 - r->stepX) / 2) / r->rayDirX;
    else
        r->perpWallDist = (r->mapY - g->player.y + (1 - r->stepY) / 2) / r->rayDirY;
    
    if (r->perpWallDist < 0.01)
        r->perpWallDist = 0.01;
    if (r->perpWallDist > 1000.0)
        r->perpWallDist = 1000.0;
}

void calc_linha(t_raio *r)
{
    r->lineHeight = (int)(WIN_H / r->perpWallDist);

    r->drawStart = -r->lineHeight / 2 + WIN_H / 2;
    if (r->drawStart < 0)
        r->drawStart = 0;
    r->drawEnd = r->lineHeight / 2 + WIN_H / 2;
    if (r->drawEnd >= WIN_H)
        r->drawEnd = WIN_H - 1;
}

void escolher_tex(t_raio *r)
{
    if (r->side == 0)
    {
        if (r->rayDirX > 0)
            r->texNum = TEX_EA;
        else
            r->texNum = TEX_WE;
    }
    else
    {
        if (r->rayDirY > 0)
            r->texNum = TEX_SO;
        else
            r->texNum = TEX_NO;
    }
}

double calc_wallX(t_game *g, t_raio *r)
{
    double wallX;
    if (r->side == 0)
        wallX = g->player.y + r->perpWallDist * r->rayDirY;
    else
        wallX = g->player.x + r->perpWallDist * r->rayDirX;
    wallX -= floor(wallX);
    return (wallX);
}

void calc_tex(t_game *g, t_raio *r, double wX)
{
    r->texX = (int)(wX * (double)g->tex[r->texNum].width);
    if (r->side == 0 && r->rayDirX < 0)
        r->texX = g->tex[r->texNum].width - r->texX - 1;
    if (r->side == 1 && r->rayDirY > 0)
        r->texX = g->tex[r->texNum].width - r->texX - 1;
    r->step = (double)g->tex[r->texNum].height / (double)r->lineHeight;
    r->texPos = (r->drawStart - WIN_H / 2 + r->lineHeight / 2) * r->step;
}

void draw_wall(t_game *g, int x, t_raio *r)
{
        int y;
        y = r->drawStart - 1;
        while (++y < r->drawEnd)
        {
            r->texY = (int)r->texPos;
            if (r->texY < 0)
                r->texY = 0;
            if (r->texY >= g->tex[r->texNum].height)
                r->texY = g->tex[r->texNum].height - 1;
            r->texPos += r->step;

            char *pixel = g->tex[r->texNum].addr
                + (r->texY * g->tex[r->texNum].line_len + r->texX * (g->tex[r->texNum].bpp / 8));
            
            int cor;
            cor = *(unsigned int*)pixel;

            my_mlx_pixel_put(&g->img, x, y, cor);
        }
}