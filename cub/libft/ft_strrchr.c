/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 04:56:00 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 20:54:23 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*s2;

	i = ft_strlen(s);
	s2 = (unsigned char *)s;
	while (i >= 0)
	{
		if (s2[i] != c)
			i--;
		else
			return ((char *)&s2[i]);
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	char *la = "Larissa testando a Jack Sparrow.";
	int ri = 'L';
	char *ret = ft_strrchr(la, ri);
	char *met = strrchr(la, ri);
	
	printf("Jack Sparrow: %s \n", ret);
	printf("Original: %s \n", met);
	return (0);
}*/
