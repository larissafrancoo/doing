/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:46:15 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/02 23:20:45 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	i = 0;
	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	while (i < n)
	{
		if (one[i] == two[i])
			i++;
		else
			return (one[i] - two[i]);
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char *s1 = "zyxbcdefgh";
	char *s2 = "abcdefgxyz";
	int n = 0;

	printf ("Original    : %d \n", memcmp(s1,s2, n));
	printf ("Jack Sparrow: %d \n", ft_memcmp(s1,s2, n));
	return (0);
}*/
