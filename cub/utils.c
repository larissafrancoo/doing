#include "cub3d.h"

int	setup_game(t_game *g, const char *path)
{
	if (!g || !path)
		return (error_exit(g, "Error\nInvalid arguments.", EXIT_F));
	ft_memset(g, 0, sizeof(t_game));
	if (open_cub(g, (char *)path))
		return (error_exit(g, "Error\nOpen_cub falied.", EXIT_F));
	if (check_integridade(g))
		return (error_exit(g, "Error\nFile integrity failure", EXIT_F));
	g->mlx = mlx_init();
	if (!g->mlx)
		return (error_exit(g, "Error\nMlx_init falied.", EXIT_F));
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "Cub3D");
	if (!g->win)
		return (error_exit(g, "Error\nMlx_new_window falied.", EXIT_F));
	g->img.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->img.img)
		return (error_exit(g, "Error\nMlx_new_image falied.", EXIT_F));
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp, &g->img.line_len,
			&g->img.endian);
	if (!g->img.addr)
		return (error_exit(g, "Error\nMlx_get_data_addr falied.", EXIT_F));
	return (EXIT_S);
}

int	check_integridade(t_game *g)
{
	if (!g)
		return (error_msg("Error\nt_game struct don't exist.", EXIT_F));
	if (!g->config.tex.no || !g->config.tex.so
		|| !g->config.tex.we || !g->config.tex.ea)
		return (error_msg("Error\nTexture is missing.", EXIT_F));
	if (g->config.chao.r < 0 || g->config.chao.r > 255
		|| g->config.chao.g < 0 || g->config.chao.g > 255
		|| g->config.chao.b < 0 || g->config.chao.b > 255)
		return (error_msg("Error\nInvalid floor color.", EXIT_F));
	if (g->config.teto.r < 0 || g->config.teto.r > 255
		|| g->config.teto.g < 0 || g->config.teto.g > 255
		|| g->config.teto.b < 0 || g->config.teto.b > 255)
		return (error_msg("Error\nInvalid celling color", EXIT_F));
	if (!g->map.grade || g->map.height <= 0 || g->map.width <= 0)
		return (error_msg("Error\nMap not loaded", EXIT_F));
	if (g->player.x < 0 || g->player.y < 0
		|| g->player.x >= g->map.width || g->player.y >= g->map.height)
		return (error_msg("Error\nInvalid player start position.", EXIT_F));
	if (!(g->player.direction == 'N' || g->player.direction == 'S'
			|| g->player.direction == 'E' || g->player.direction == 'W'))
		return (error_msg("Error\nInvalid player direction.", EXIT_F));
	return (EXIT_S);
}

int	load_tex(t_game *g, t_infos *t, char *path)
{
	t->img = mlx_xpm_file_to_image(g->mlx, (char *)path, &t->width, &t->height);
	if (!t->img)
		return (error_msg("Error\nFalied to load texture.", EXIT_F));
	if (access(path, R_OK) != 0)
		return (error_msg("Error\nTexture file doesn't exist.", EXIT_F));
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	if (!t->addr || t->width <= 0 || t->height <= 0)
		return (error_msg("Error\nFailure in addr, width, or height.", EXIT_F));
	return (EXIT_S);
}

int	load_all_texs(t_game *g)
{
	if (load_tex(g, &g->tex[TEX_NO], g->config.tex.no))
		return (error_msg("Error\nFalied to load texture NO.", EXIT_F));
	if (load_tex(g, &g->tex[TEX_SO], g->config.tex.so))
		return (error_msg("Error\nFalied to load texture SO.", EXIT_F));
	if (load_tex(g, &g->tex[TEX_WE], g->config.tex.we))
		return (error_msg("Error\nFalied to load texture WE.", EXIT_F));
	if (load_tex(g, &g->tex[TEX_EA], g->config.tex.ea))
		return (error_msg("Error\nFalied to load texture EA.", EXIT_F));
	return (EXIT_S);
}

int	render_frame(t_game *g)
{
	int		x;
	double	wall_x;
	t_raio	r;

	x = -1;
	if (prepara_frame(g))
		return (error_msg("Error\nFrame preparation failure.", EXIT_F));
	limpa_bkg(g);
	x = -1;
	while (++x < WIN_W)
	{
		inicializar_raio(g, x, &r);
		exec_dda(g, &r);
		calc_linha(&r);
		escolher_tex(&r);
		wall_x = calc_wall_x(g, &r);
		calc_tex(g, &r, wall_x);
		draw_wall(g, x, &r);
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (EXIT_S);
}
