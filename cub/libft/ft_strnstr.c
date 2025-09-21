/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 06:39:30 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/09 16:44:57 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check(const char *b, const char *l, size_t len, size_t i)
{
	size_t	size;
	size_t	index;
	size_t	count;

	size = ft_strlen(l);
	index = 0;
	count = 0;
	while ((b[i] != '\0') && (i <= len) && (index <= size))
	{
		if (b[i] == l[index])
			count++;
		index++;
		i++;
	}
	if (count != size)
		return (0);
	else
		return (-1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		o;
	char	*bi;

	i = 0;
	o = 0;
	if ((!big || !little) && !len)
		return (NULL);
	bi = (char *)big;
	if (little[0] == '\0')
		return (bi);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			o = check(big, little, len, i);
			if (o == -1)
				return (&bi[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int main(void)
{
	char *one = "Gustavo gosta de chocolate";
	char *two = "";
	int len = 0;
	
	char *ret = ft_strnstr(one, two, len);
	printf("Jack Sparrow: %s \n", ret);
	char *ori = strnstr(one, two, len);
	printf("Original    : %s \n", ori);
	return (0);
}*/
