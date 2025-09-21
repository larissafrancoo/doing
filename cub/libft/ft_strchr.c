/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:53:31 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 22:11:11 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *)s;
	while (s2[i] != '\0')
	{
		if (s2[i] != c)
			i++;
		else
			return ((char *)&s2[i]);
	}
	if (c == '\0')
		return ((char *)&s2[i]);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s = "\0";
	int c = 'l';

	printf("Jack Sparrow: %s - Endereço: %p \n", ft_strchr(s, c), ft_strchr(s, c));
	printf("Original    : %s - Endereço: %p \n", strchr(s, c), strchr(s, c));
	return (0);
}*/
