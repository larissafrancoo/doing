/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:51 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 22:07:27 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_str;
	unsigned char	*dest_str;

	if (!src && !dest)
		return (NULL);
	src_str = (unsigned char *)src;
	dest_str = (unsigned char *)dest;
	if (src_str < dest_str)
	{
		while (n--)
			dest_str[n] = src_str[n];
	}
	else
	{
		i = -1;
		while (++i < n)
			dest_str[i] = src_str[i];
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char dest_o[19] = "larissa testando...";
	char src_o[7] = "lfranco";
	char dest_jack[19] = "larissa testando...";
	char src_jack[7] = "lfranco";
	int size = 5;

	char *retOri = memmove(dest_o, src_o, size);
	char *retJack = ft_memmove(dest_jack, src_jack, size);

	printf("Original: %s \n", retOri);
	printf("Endereço ori: %p \n\n", retOri);
	printf("Jack Sparrow: %s \n", retJack);
	printf("Endereço Jack: %p \n\n", retJack);
	return (0);
}*/
