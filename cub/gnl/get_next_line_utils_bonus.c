/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:12:50 by lfranco           #+#    #+#             */
/*   Updated: 2024/02/01 23:13:14 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_n(char *line)
{
	int	count;

	if (!line)
		return (0);
	count = 0;
	while (line[count])
	{
		if (line[count] == '\n')
			return (count);
		count++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*my_ft_strjoin(char *buffer, char *line)
{
	char	*str;
	int		i;

	str = (char *)malloc(ft_strlen(buffer) + ft_strlen(line) + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			str[i] = buffer[i];
			i++;
		}
		free(buffer);
	}
	while (*line)
		str[i++] = *line++;
	str[i] = '\0';
	if (!*str)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*the_first_part_of(char *buffer)
{
	char	*line;
	int		i;
	int		size;
	int		check;

	size = 0;
	check = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	if (buffer[size] == '\n')
		check++;
	line = (char *)malloc(sizeof(char) * (size + check + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < size)
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*the_second_part_of(char *buffer)
{
	char	*new_res;
	int		i;
	int		size;

	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	if (!buffer[size])
	{
		free(buffer);
		return (NULL);
	}
	size++;
	new_res = malloc((ft_strlen(buffer) - size + 1) * sizeof(char));
	if (!new_res)
		return (NULL);
	i = 0;
	while (buffer[size + i])
	{
		new_res[i] = buffer[size + i];
		i++;
	}
	new_res[i] = '\0';
	free(buffer);
	return (new_res);
}
