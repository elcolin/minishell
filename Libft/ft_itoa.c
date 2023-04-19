/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenayou <rbenayou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:17:47 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/17 02:18:11 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_atoi_4_itoa(char *tab, long nb, long size)
{
	while (nb)
	{
		tab[size] = (nb % 10) + '0';
		nb = nb / 10;
		size--;
	}
	return (tab);
}

static size_t	ft_str_int_len(long nbr)
{
	size_t	i;

	i = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	if (nbr == 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(long n)
{
	char	*tab;
	size_t	nb;
	size_t	size;

	size = ft_str_int_len(n);
	if (n <= -9223372036854775807 || n > 9223372036854775807)
		return ("0");
	tab = ft_malloc(sizeof(*tab) * (unsigned long)size + 1);
	if (!tab)
		return (NULL);
	tab[size] = '\0';
	size--;
	if (n == 0)
		tab[0] = '0';
	if (n < 0)
	{
		nb = -n;
		tab[0] = '-';
	}
	else
		nb = n;
	tab = ft_atoi_4_itoa(tab, nb, size);
	return (tab);
}
