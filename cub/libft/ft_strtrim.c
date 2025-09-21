/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:01:27 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 17:10:30 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		o;
	char	*ret;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	o = (ft_strlen(s1) - 1);
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) != NULL)
			i++;
		else
			break ;
	}
	while (o > i)
	{
		if (ft_strchr(set, s1[o]) != NULL)
			o--;
		else
			break ;
	}
	ret = ft_substr(s1, i, (++o - i));
	return (ret);
}
/*
#include <stdio.h>
int main(void)
{
	char *sone = "123123jacksparowwwww123";
	char *sit = "";
	char *ret = ft_strtrim(sone, sit);

	printf("Retorno: %s \n", ret);
	free(ret);
	return (0);
}*/
