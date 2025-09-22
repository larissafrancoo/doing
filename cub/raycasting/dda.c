/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:05:53 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:05:54 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
