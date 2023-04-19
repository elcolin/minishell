/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:55:13 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/17 02:16:05 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	n_occurencies(char *s, char c, int n)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i] && i < n)
	{
		if (s[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

char	*ft_strndup(const char *s, int n)
{
	size_t	i;
	size_t	j;
	char	*cpy;

	i = 0;
	j = 0;
	if (n == -1 || n > (int) ft_strlen(s))
		n = ft_strlen(s);
	n -= n_occurencies((char *)s, -1, n);
	cpy = ft_malloc(n + 1);
	if (!cpy)
		return (0);
	while ((int) i < n && s[i + j])
	{
		if (s[i + j] != -1)
		{
			cpy[i] = s[i + j];
			i++;
		}
		else
			j++;
	}
	cpy[n] = '\0';
	return (cpy);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = ft_malloc(ft_strlen(s) + 1);
	if (!cpy || !s)
		return (0);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = s[i];
	return (cpy);
}
