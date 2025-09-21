/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:59:41 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/01 01:14:05 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	index;
	size_t	len_src;

	index = 0;
	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	while (index < (size - 1) && src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (len_src);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int main(void)
{
	char *src = "abcdefghij";
	char dO[12] = "0";
	char dJack[12] = "0";
	int size = 8;
	unsigned int retO = strlcpy(dO, src, size);
	unsigned int retJack = ft_strlcpy(dJack, src, size);

	printf("Retorno original: %d;\n", retO);
	printf("Dest ori: %s \n", dO);
	printf("Tamanho de dest ori: %ld \n\n", ft_strlen(dO));
	
	printf("Retorno Jack Sparrow: %d;\n", retJack);
	printf("Dest Jack: %s \n", dJack);
	printf("Tamanho de dest Jack: %ld \n\n", ft_strlen(dJack));
	return (0);
}*/
