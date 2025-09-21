/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:29:01 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/02 22:56:43 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s_one;
	unsigned char	*s_two;

	i = 0;
	s_one = (unsigned char *)s1;
	s_two = (unsigned char *)s2;
	while (i < n)
	{
		if ((s_one[i] == s_two[i])
			&& (s_one[i] != '\0' || s_two[i] != '\0'))
			i++;
		else
			return (s_one[i] - s_two[i]);
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char	*la = "test\200";
	char	*ri = "test\0";
	int	s = 6;

	printf("Jack Sparrow: %d \n", ft_strncmp(la, ri, s));
	printf("Original    : %d \n", strncmp(la, ri, s));
	return (0);
}*/
