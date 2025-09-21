/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 05:05:21 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/09 12:52:53 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_s;
	size_t	len_d;
	size_t	len_finish;

	i = 0;
	len_s = ft_strlen(src);
	if (size == 0)
		return (len_s);
	len_d = ft_strlen(dst);
	if (len_d >= size)
		return (size + len_s);
	else
		len_finish = len_d + len_s;
	while (src[i] && len_d < (size - 1))
	{
		dst[len_d] = src[i];
		len_d++;
		i++;
	}
	dst[len_d] = '\0';
	return (len_finish);
}
/*
#include <bsd/string.h>
#include <stdio.h>

int main(void)
{
//	char d[15];
//	d[14] = 'a';
	char *d = NULL;
	char b[0xF] = "lari !";
//	int ret = strlcat(d, "lorem ipsum dolor sit amet", 0);
	int ret = ft_strlcat(d, b, 0);
	
	printf("Retorno   : %d \n", ret);
	printf("dst1 after: %p - %s \n\n", d, d);

	return (0);
}*/
