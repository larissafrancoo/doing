/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:03:44 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:03:46 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_texs(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (g->tex[i].img)
		{
			mlx_destroy_image(g->mlx, g->tex[i].img);
			g->tex[i].img = NULL;
			g->tex[i].addr = NULL;
		}
	}
}

void	free_map(t_map *m)
{
	int	i;

	i = -1;
	if (!m || !m->grade)
		return ;
	while (++i < m->height)
	{
		free(m->grade[i]);
		m->grade[i] = NULL;
	}
	free(m->grade);
	m->grade = NULL;
	m->height = 0;
	m->width = 0;
}

void	free_config(t_config *c)
{
	if (!c)
		return ;
	free(c->tex.no);
	free(c->tex.so);
	free(c->tex.we);
	free(c->tex.ea);
	c->tex.no = NULL;
	c->tex.so = NULL;
	c->tex.we = NULL;
	c->tex.ea = NULL;
}

void	free_player(t_player *p)
{
	if (!p)
		return ;
	p->x = 0;
	p->y = 0;
	p->dx = 0;
	p->dy = 0;
	p->px = 0;
	p->py = 0;
	p->direction = '\0';
}

void	free_all(t_game *g)
{
	if (!g)
		return ;
	destroy_texs(g);
	if (g->img.img)
	{
		mlx_destroy_image(g->mlx, g->img.img);
		g->img.img = NULL;
	}
	free_map(&g->map);
	free_config(&g->config);
	free_player(&g->player);
	if (g->win)
	{
		mlx_destroy_window(g->mlx, g->win);
		g->win = NULL;
	}
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		g->mlx = NULL;
	}
}
