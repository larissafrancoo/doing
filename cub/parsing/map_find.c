/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:04:32 by lfranco           #+#    #+#             */
/*   Updated: 2025/09/22 00:04:33 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

static int	is_map_line(const char *s)
{
	int	i;
	int	has_symbol;

	if (!s)
		return (0);
	i = 0;
	has_symbol = 0;
	while (s[i] && s[i] != '\n')
	{
		if (!is_valid_char(s[i]))
			return (0);
		if (s[i] != ' ')
			has_symbol = 1;
		i++;
	}
	return (has_symbol);
}

int	find_map_start(char **lines, int lcount)
{
	int	i;

	i = -1;
	while (++i < lcount)
	{
		if (lines[i][0] == '\n')
		{
			i++;
			continue ;
		}
		if (is_config_line(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_map_line(lines[i]))
			return (i);
	}
	return (-1);
}

int	validate_after_map(char **lines, int start_map, int lcount)
{
	int	i;

	i = start_map;
	while (i < lcount)
	{
		if (lines[i][0] != '\n' && !is_map_line(lines[i]))
			return (error_msg("Error\nInvalid line after map block.",
					EXIT_F));
		i++;
	}
	return (EXIT_S);
}
