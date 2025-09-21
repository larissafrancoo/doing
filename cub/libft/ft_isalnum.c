/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:59:04 by lfranco           #+#    #+#             */
/*   Updated: 2023/11/10 22:04:54 by lfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (8);
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	printf("Result Digit: %d.\n", ft_isalnum('6'));
	printf("Result Lowcase: %d.\n", ft_isalnum('a'));
	printf("Result Uppercase: %d.\n", ft_isalnum('H'));
	printf("Result Non_alnum: %d.\n", ft_isalnum('+'));
	return (0);
}*/
