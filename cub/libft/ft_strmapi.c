/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:07:14 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 21:52:15 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str || !f)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
char    my_function(unsigned int i, char alpha)
{
    (void)i;
    if (alpha >= 97 && alpha <= 122)
        alpha = alpha - 32;
    return (alpha);
}

int    main(void)
{
    char const    str[] ="Teste 123 Go.";
    char        *s;

    s = ft_strmapi(str, my_function);
    printf("%s \n", s);
    free(s);
    return (0);
}*/
