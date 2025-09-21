#include "cub3d.h"

int setup_game(t_game *g, const char *path)
{
    if (!g || !path)
        return error_exit(g, "Error\n[setup_game] Argumentos inválidos.", EXIT_FAILURE);
    ft_memset(g, 0, sizeof(t_game));
    if (open_cub(g, (char *)path))
        return (error_exit(g, "Error\n[setup_game] A open_cub falhou.", EXIT_FAILURE));
    if (check_integridade(g))
        return (error_exit(g, "Error\n[setup_game] Falha de integridade no arquivo .cub.", EXIT_FAILURE));
    g->mlx = mlx_init();
    if (!g->mlx)
        return (error_exit(g, "Error\n[setup_game] A mlx_init falhou.", EXIT_FAILURE));
    g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "Cub3D");
    if (!g->win)
        return (error_exit(g, "Error\n[setup_game] A mlx_new_window falhou.", EXIT_FAILURE));
    g->img.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
    if (!g->img.img)
        return (error_exit(g, "Error\n[setup_game] A mlx_new_image falhou.", EXIT_FAILURE));
    g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp, &g->img.line_len, &g->img.endian);
    if (!g->img.addr)
        return (error_exit(g, "Error\n[setup_game] A mlx_get_data_addr falhou.", EXIT_FAILURE));
    return (EXIT_SUCCESS);
}

int check_integridade(t_game *g)
{
    if (!g)
        return (error_msg("Error\n[check_integridade] A struct t_game não exite.", EXIT_FAILURE));
    print_game(g); //[DEBUG]
    if (!g->config.tex.no || !g->config.tex.so || 
        !g->config.tex.we || !g->config.tex.ea)
        return (error_msg("Error\n[check_integridade] Está faltando textura.", EXIT_FAILURE));
    if (g->config.chao.r < 0 || g->config.chao.r > 255 ||
        g->config.chao.g < 0 || g->config.chao.g > 255 ||
        g->config.chao.b < 0 || g->config.chao.b > 255)
        return (error_msg("Error\n[check_integridade] Cor do chão inválida.", EXIT_FAILURE));
    if (g->config.teto.r < 0 || g->config.teto.r > 255 ||
        g->config.teto.g < 0 || g->config.teto.g > 255 ||
        g->config.teto.b < 0 || g->config.teto.b > 255)
        return (error_msg("Error\n[check_integridade] Cor do teto inválida.", EXIT_FAILURE));
    if (!g->map.grade || g->map.height <= 0 || g->map.width <= 0)
        return (error_msg("Error\n[check_integridade] Mapa não carregado.", EXIT_FAILURE));
    if (g->player.x < 0 || g->player.y < 0 ||
        g->player.x >= g->map.width || g->player.y >= g->map.height)
        return (error_msg("Error\n[check_integridade] Posição inicial do jogador inválida.", EXIT_FAILURE));
    if (!(g->player.direction == 'N' || g->player.direction == 'S' ||
          g->player.direction == 'E' || g->player.direction == 'W'))
        return (error_msg("Error\n[check_integridade] Direção do jogador inválida.", EXIT_FAILURE));
    return (EXIT_SUCCESS);
}

int load_tex(t_game *g, t_infos *t, char *path)
{
    t->img = mlx_xpm_file_to_image(g->mlx, (char *)path, &t->width, &t->height);
    if (!t->img)
        return (error_msg("Error\n[load_tex] Falha ao carregar a textura.", EXIT_FAILURE));
    if (access(path, R_OK) != 0)
        return (error_msg("Error\n[load_tex] Arquivo de textura inexistente.", EXIT_FAILURE));
    t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
    if (!t->addr || t->width <= 0 || t->height <= 0)
        return (error_msg("Error\n[load_tex] Falha no addr, width ou height.", EXIT_FAILURE));
    return (EXIT_SUCCESS);
}

int load_all_texs(t_game *g)
{
    if (load_tex(g, &g->tex[TEX_NO], g->config.tex.no))
        return (error_msg("Error\n[load_all_texs] Falha ao carregar a textura NO.", EXIT_FAILURE));
    if (load_tex(g, &g->tex[TEX_SO], g->config.tex.so))
        return (error_msg("Error\n[load_all_texs] Falha ao carregar a textura SO.", EXIT_FAILURE));
    if (load_tex(g, &g->tex[TEX_WE], g->config.tex.we))
        return (error_msg("Error\n[load_all_texs] Falha ao carregar a textura WE.", EXIT_FAILURE));
    if (load_tex(g, &g->tex[TEX_EA], g->config.tex.ea))
        return (error_msg("Error\n[load_all_texs] Falha ao carregar a textura EA.", EXIT_FAILURE));
    return (EXIT_SUCCESS);
}

int render_frame(t_game *g)
{
    int x;

    x = -1;
    if (prepara_frame(g))
        return (error_msg("Error\n[render_frame] Falha na preparação do frame.", EXIT_FAILURE));
    limpa_bkg(g);
    x = -1;
    while (++x < WIN_W)
    {
        t_raio r;
        inicializar_raio(g, x, &r);
        exec_dda(g, &r);
        calc_linha(&r);
        escolher_tex(&r);
        double wallX = calc_wallX(g, &r);
        calc_tex(g, &r, wallX);
        draw_wall(g, x, &r);
    }

    mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
    return (EXIT_SUCCESS);
}