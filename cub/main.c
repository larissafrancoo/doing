/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:02:22 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:02:36 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_game(t_game *g, const char *path)
{
	if (setup_game(g, path))
		return (error_exit(g, "Error\nSetup game failure.", EXIT_F));
	if (load_all_texs(g))
		return (error_exit(g, "Error\nFalied to load textures.", EXIT_F));
	if (render_frame(g))
		return (game_over(g));
	return (EXIT_S);
}

int	main(int ac, char **av)
{
	t_game	g;

	if (ac != 2)
	{
		fprintf(stderr, "Error\nIncorrect entry."
			"Usage: %s <map_path.cub>\n", av[0]);
		return (EXIT_F);
	}
	if (check_extension(av[1], ".cub"))
	{
		fprintf(stderr, "Error\nIncorrect entry."
			"Usage: %s <map_path.cub>\n", av[0]);
		return (EXIT_F);
	}
	if (init_game(&g, av[1]))
		return (EXIT_F);
	mlx_hook(g.win, 17, 0, game_over, &g);
	mlx_key_hook(g.win, handle_key, &g);
	mlx_loop(g.mlx);
	game_over(&g);
	return (EXIT_S);
}
