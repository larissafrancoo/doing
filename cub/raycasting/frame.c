/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:06:08 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:06:10 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	rgb_to_int(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
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

int	render_frame(t_game *g)
{
	int		x;
	double	wall_x;
	t_ray	r;

	x = -1;
	if (prepare_frame(g))
		return (error_msg("Error\nFrame preparation failure.", EXIT_F));
	clean_bkg(g);
	x = -1;
	while (++x < WIN_W)
	{
		ray_initialize(g, x, &r);
		exec_dda(g, &r);
		calc_line(&r);
		choose_tex(&r);
		wall_x = calc_wall_x(g, &r);
		calc_tex(g, &r, wall_x);
		draw_wall(g, x, &r);
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (EXIT_S);
}
