/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:04:56 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:04:57 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	set_values(t_player *p, char dir, double v1, double v2)
{
	if (dir == 'N')
	{
		p->dy = -v1;
		p->px = v2;
	}
	else if (dir == 'S')
	{
		p->dy = v1;
		p->px = -v2;
	}
	else if (dir == 'E')
	{
		p->dx = v1;
		p->py = v2;
	}
	else if (dir == 'W')
	{
		p->dx = -v1;
		p->py = -v2;
	}
	else
		return (EXIT_F);
	return (EXIT_S);
}

int	set_direction(t_player *player)
{
	if (!player || !player->direction)
		return (error_msg("Error\nRealloc failure.", EXIT_F));
	if (set_values(player, player->direction, 1, 0.66))
		return (error_msg("Error\nSet direction failure.", EXIT_F));
	return (EXIT_S);
}

int	set_player(t_player *player, int x, int y, char dir)
{
	if (player->direction)
		return (error_msg("Error\nThere is more than one player on the map.",
				EXIT_F));
	player->x = x + 0.5;
	player->y = y + 0.5;
	player->direction = dir;
	if (set_direction(player))
		return (error_msg("Error\nFailed to set direction.", EXIT_F));
	return (EXIT_S);
}
