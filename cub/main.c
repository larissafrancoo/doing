#include "cub3d.h"

static int init_game(t_game *g, const char *path)
{
    if (setup_game(g, path))
        return (error_exit(g, "Error\n[init_game] Falha no setup do jogo. Abortando...", EXIT_FAILURE));
    // if (check_integridade(g))
    //     return (error_exit(g, "Error\n[init_game] Falha na verificação inicial de integridade. Abortando...", EXIT_FAILURE));
    if (load_all_texs(g))
        return (error_exit(g, "Error\n[init_game] Falha ao carregar as texturas. Abortando...", EXIT_FAILURE));
    if (render_frame(g))
        return (game_over(g));
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    t_game g = {0};
    // print_game(&g); //[DEBUG]

    if (ac != 2) {
        fprintf(stderr, "Error\n[main] Incorrect entry. Usage: %s <map_path.cub>\n", av[0]);
        return (EXIT_FAILURE);
    }

    if (init_game(&g, av[1]))
        return (EXIT_FAILURE);

    mlx_hook(g.win, 17, 0, game_over, &g);
    mlx_key_hook(g.win, handle_key, &g);
    mlx_loop(g.mlx);

    game_over(&g);
    return (EXIT_SUCCESS);
}

void print_game(t_game *game) {
    printf("t_game:\n");
    printf("  mlx: %p\n", game->mlx);
    printf("  win: %p\n", game->win);

    // t_infos img
    printf("  img:\n");
    printf("    img: %p\n", game->img.img);
    printf("    addr: %s\n", game->img.addr ? game->img.addr : "(null)");
    printf("    bpp: %d\n", game->img.bpp);
    printf("    line_len: %d\n", game->img.line_len);
    printf("    endian: %d\n", game->img.endian);
    printf("    width: %d\n", game->img.width);
    printf("    height: %d\n", game->img.height);

    // texturas
    for (int i = 0; i < MAX_TEX; i++) {
        printf("  tex[%d]:\n", i);
        printf("    img: %p\n", game->tex[i].img);
        printf("    addr: %s\n", game->tex[i].addr ? game->tex[i].addr : "(null)");
        printf("    bpp: %d\n", game->tex[i].bpp);
        printf("    line_len: %d\n", game->tex[i].line_len);
        printf("    endian: %d\n", game->tex[i].endian);
        printf("    width: %d\n", game->tex[i].width);
        printf("    height: %d\n", game->tex[i].height);
    }

    // t_config
    printf("  config:\n");
    printf("    chao: r=%d g=%d b=%d\n", game->config.chao.r, game->config.chao.g, game->config.chao.b);
    printf("    teto: r=%d g=%d b=%d\n", game->config.teto.r, game->config.teto.g, game->config.teto.b);
    printf("    tex:\n");
    printf("      no: %s\n", game->config.tex.no ? game->config.tex.no : "(null)");
    printf("      so: %s\n", game->config.tex.so ? game->config.tex.so : "(null)");
    printf("      we: %s\n", game->config.tex.we ? game->config.tex.we : "(null)");
    printf("      ea: %s\n", game->config.tex.ea ? game->config.tex.ea : "(null)");

    // t_map
    printf("  map:\n");
    printf("    width: %d\n", game->map.width);
    printf("    height: %d\n", game->map.height);
    if (game->map.grade) {
        printf("    grade:\n");
        for (int i = 0; i < game->map.height; i++) {
            printf("      %s\n", game->map.grade[i]);
        }
    } else {
        printf("    grade: (null)\n");
    }

    // t_player
    printf("  player:\n");
    printf("    x: %f\n", game->player.x);
    printf("    y: %f\n", game->player.y);
    printf("    dx: %f\n", game->player.dx);
    printf("    dy: %f\n", game->player.dy);
    printf("    px: %f\n", game->player.px);
    printf("    py: %f\n", game->player.py);
    printf("    direction: %c\n", game->player.direction);
}