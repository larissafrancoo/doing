/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:10:09 by lfranco           #+#    #+#             */
/*   Updated: 2024/02/01 23:11:18 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_buffer(int fd)
{
	char		*line;
	static char	*buffer[MAX_FD];
	int			ret_read;

	line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ret_read = 1;
	while (ret_read > 0 && !find_n(buffer[fd]))
	{
		ret_read = read(fd, line, BUFFER_SIZE);
		if (ret_read < 0)
		{
			free(line);
			return (NULL);
		}
		line[ret_read] = '\0';
		buffer[fd] = my_ft_strjoin(buffer[fd], line);
	}
	free(line);
	if (!buffer[fd])
		return (NULL);
	line = the_first_part_of(buffer[fd]);
	buffer[fd] = the_second_part_of(buffer[fd]);
	return (line);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_buffer(fd));
}
/*
#include <fcntl.h>
#include <stdio.h>
int main ()
{
	int fd = open("text.txt", O_RDONLY);

	char *line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}	
}
*/
