/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:59:12 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 21:23:46 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	n_len(long int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int				len;
	long int		temp;
	char			*str;

	len = n_len(n);
	temp = (long int)n;
	str = (char *) ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (temp == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (temp < 0)
	{
		str[0] = '-';
		temp *= -1;
	}
	while (temp > 0)
	{
		str[--len] = (temp % 10) + '0';
		temp /= 10;
	}
	return (str);
}
/*
#include <stdio.h>
int main(void)
{
	const int nu = -2147483648;
	char *ret = ft_itoa(nu);

	printf("Result: %s \n", ret);
	return (0);
}*/
