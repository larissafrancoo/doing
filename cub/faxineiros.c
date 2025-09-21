#include "cub3d.h"

int	error_exit(t_game *g, const char *msg, int code)
{
	if (msg)
		fprintf(stderr, "%s\n", msg);
	if (g)
		free_all(g);
	return (code);
}

int	error_msg(const char *msg, int code)
{
	if (msg)
		fprintf(stderr, "%s\n", msg);
	return (code);
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

void	destroi_texs(t_game *g)
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
	destroi_texs(g);
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

int	close_game(t_game *g)
{
	free_all(g);
	exit(0);
	return (0);
}

int	game_over(t_game *g)
{
	free_all(g);
	exit(0);
	return (0);
}
