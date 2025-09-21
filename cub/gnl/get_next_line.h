/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:08:50 by lfranco           #+#    #+#             */
/*   Updated: 2024/02/01 23:13:28 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif 

# include <unistd.h>
# include <stdlib.h>

int		find_n(char *line);
char	*my_ft_strjoin(char *buffer, char *line);
char	*the_second_part_of(char *buffer);
char	*the_first_part_of(char *buffer);
char	*get_next_line(int fd);

#endif
