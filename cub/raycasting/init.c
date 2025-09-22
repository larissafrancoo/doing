/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:06:15 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:06:16 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
