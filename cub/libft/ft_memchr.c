/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:49:20 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 22:07:04 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = (char *)s;
	while (i < n)
	{
		if (s2[i] == c)
			return ((char *)&s2[i]);
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	char *s = "larissa testando a função";
	int c = 'a';
	int n = 2;

	printf("Original: %s \n", (char *) ft_memchr(s, c, n));
	printf("Jack Sparrow: %s \n", (char *) memchr(s, c, n));
	return (0);
}*/
