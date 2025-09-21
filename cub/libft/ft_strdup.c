/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <lfranco@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:42:26 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 21:11:50 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*dup;

	i = 0;
	len = (ft_strlen(s) + 1);
	dup = (char *) ft_calloc(len, sizeof(char));
	if (!dup)
		return (NULL);
	while (i != len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	const char *s = "12345";
	char *ret = ft_strdup(s);
	printf ("Jack Sparrow: %s \n", ret);
	return (0);
}*/
