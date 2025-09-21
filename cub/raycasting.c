#include "cub3d.h"

void	my_mlx_pixel_put(t_infos *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr)
		return ;
	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_h_line(t_game *g, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		my_mlx_pixel_put(&g->img, x, y, color);
		y++;
	}
}

int	rgb_to_int(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}

int	prepare_frame(t_game *g)
{
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	g->img.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->img.img)
		return (error_msg("Error\nFailed to create new image.",
				EXIT_F));
	g->img.addr = mlx_get_data_addr(g->img.img,
			&g->img.bpp, &g->img.line_len, &g->img.endian);
	if (!g->img.addr)
		return (error_msg("Error\nFailed to get addr", EXIT_F));
	return (EXIT_S);
}

void	clean_bkg(t_game *g)
{
	int	x;
	int	y;
	int	c;
	int	t;

	c = rgb_to_int(g->config.floor);
	t = rgb_to_int(g->config.cell);
	y = -1;
	while (++y < WIN_H / 2)
	{
		x = -1;
		while (++x < WIN_W)
			my_mlx_pixel_put(&g->img, x, y, t);
	}
	y = WIN_H / 2 - 1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			my_mlx_pixel_put(&g->img, x, y, c);
	}
}

void	calc_direction(t_game *g, int x, t_ray *r)
{
	r->cam_x = 2 * x / (double)WIN_W - 1;
	r->r_dir_x = g->player.dx + g->player.px * r->cam_x;
	r->r_dir_y = g->player.dy + g->player.py * r->cam_x;
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
}

void	calc_delta(t_ray *r)
{
	if (r->r_dir_x == 0)
		r->delt_dis_x = 1e30;
	else
		r->delt_dis_x = fabs(1 / r->r_dir_x);
	if (r->r_dir_y == 0)
		r->delt_dis_y = 1e30;
	else
		r->delt_dis_y = fabs(1 / r->r_dir_y);
}

void	calc_steps(t_game *g, t_ray *r)
{
	r->step_x = 1;
	r->step_y = 1;
	if (r->r_dir_x < 0)
	{
		r->step_x = -1;
		r->sid_dis_x = (g->player.x - r->map_x) * r->delt_dis_x;
	}
	else
		r->sid_dis_x = (r->map_x + 1.0 - g->player.x) * r->delt_dis_x;
	if (r->r_dir_y < 0)
	{
		r->step_y = -1;
		r->sid_dis_y = (g->player.y - r->map_y) * r->delt_dis_y;
	}
	else
		r->sid_dis_y = (r->map_y + 1.0 - g->player.y) * r->delt_dis_y;
}

void	ray_initialize(t_game *g, int x, t_ray *r)
{
	calc_direction(g, x, r);
	calc_delta(r);
	calc_steps(g, r);
	r->hit = 0;
}

void	take_step(t_ray *r)
{
	if (r->sid_dis_x < r->sid_dis_y)
	{
		r->sid_dis_x += r->delt_dis_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->sid_dis_y += r->delt_dis_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

void	exec_dda(t_game *g, t_ray *r)
{
	int	max_steps;

	max_steps = 1000;
	while (!r->hit && max_steps--)
	{
		take_step(r);
		if (g->map.grade[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
	if (!r->hit)
		r->per_wll_dis = 1000.0;
	if (r->side == 0)
		r->per_wll_dis = (r->map_x - g->player.x
				+ (1 - r->step_x) / 2) / r->r_dir_x;
	else
		r->per_wll_dis = (r->map_y - g->player.y
				+ (1 - r->step_y) / 2) / r->r_dir_y;
	if (r->per_wll_dis < 0.01)
		r->per_wll_dis = 0.01;
	if (r->per_wll_dis > 1000.0)
		r->per_wll_dis = 1000.0;
}

void	calc_line(t_ray *r)
{
	r->line_h = (int)(WIN_H / r->per_wll_dis);
	r->drw_start = -r->line_h / 2 + WIN_H / 2;
	if (r->drw_start < 0)
		r->drw_start = 0;
	r->drw_end = r->line_h / 2 + WIN_H / 2;
	if (r->drw_end >= WIN_H)
		r->drw_end = WIN_H - 1;
}

void	choose_tex(t_ray *r)
{
	if (r->side == 0)
	{
		if (r->r_dir_x > 0)
			r->tex_nu = TEX_EA;
		else
			r->tex_nu = TEX_WE;
	}
	else
	{
		if (r->r_dir_y > 0)
			r->tex_nu = TEX_SO;
		else
			r->tex_nu = TEX_NO;
	}
}

double	calc_wall_x(t_game *g, t_ray *r)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = g->player.y + r->per_wll_dis * r->r_dir_y;
	else
		wall_x = g->player.x + r->per_wll_dis * r->r_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	calc_tex(t_game *g, t_ray *r, double wX)
{
	r->tx_x = (int)(wX * (double)g->tex[r->tex_nu].width);
	if (r->side == 0 && r->r_dir_x < 0)
		r->tx_x = g->tex[r->tex_nu].width - r->tx_x - 1;
	if (r->side == 1 && r->r_dir_y > 0)
		r->tx_x = g->tex[r->tex_nu].width - r->tx_x - 1;
	r->step = (double)g->tex[r->tex_nu].height / (double)r->line_h;
	r->tx_pos = (r->drw_start - WIN_H / 2 + r->line_h / 2) * r->step;
}

void	draw_wall(t_game *g, int x, t_ray *r)
{
	int		y;
	int		cor;
	char	*pixel;

	y = r->drw_start - 1;
	while (++y < r->drw_end)
	{
		r->tx_y = (int)r->tx_pos;
		if (r->tx_y < 0)
			r->tx_y = 0;
		if (r->tx_y >= g->tex[r->tex_nu].height)
			r->tx_y = g->tex[r->tex_nu].height - 1;
		r->tx_pos += r->step;
		pixel = g->tex[r->tex_nu].addr
			+ (r->tx_y * g->tex[r->tex_nu].line_len + r->tx_x
				* (g->tex[r->tex_nu].bpp / 8));
		cor = *(unsigned int *)pixel;
		my_mlx_pixel_put(&g->img, x, y, cor);
	}
}
