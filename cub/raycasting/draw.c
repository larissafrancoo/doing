/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:05:59 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:06:02 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	draw_wall(t_game *g, int x, t_ray *r)
{
	int		y;
	int		color;
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
		color = *(unsigned int *)pixel;
		my_mlx_pixel_put(&g->img, x, y, color);
	}
}
