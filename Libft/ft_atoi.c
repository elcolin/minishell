/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:49:22 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/15 05:50:58 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

long	ft_atoi(const char *nptr)
{
	long	i;
	long	res;
	long	p;

	i = 0;
	res = 0;
	p = 1;
	if (!nptr)
		return (0);
	while ((nptr[i] <= 13 && nptr[i] >= 9) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		p = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (res * p);
		res += nptr[i] - '0';
		i++;
		if (nptr[i] != '\0' && (nptr[i] <= '9' && nptr[i] >= '0'))
			res *= 10;
	}
	return (res * p);
}
