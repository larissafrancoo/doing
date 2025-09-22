/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:03:25 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:03:26 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	game_over(t_game *g)
{
	free_all(g);
	exit(0);
	return (0);
}
