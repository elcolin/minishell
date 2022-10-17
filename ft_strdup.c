/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:55:13 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/17 17:45:53 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *s, int n)
{
	size_t	i;
	size_t	j;
	char	*cpy;
	int	quote;

	quote = 0;
	i = 0;
	j = 0;
	if (n == -1)
		n = ft_strlen(s);
	cpy = malloc(n + 1);
	if (!cpy)
		return (0);
	while (i < n && s[i + j])
	{
		if ((s[i + j] == '\'' || s[i + j] == '"') && !quote)
		{
			quote = s[i];
			j++;
		}
		else if (s[i + j] == quote && quote)
		{
			quote = 0;
			j++;
		}
		else
		{
			cpy[i] = s[i + j];
			i++;
		}
	}
	cpy[i] = 0;
	return (cpy);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = malloc(ft_strlen(s) + 1);
	if (!cpy)
		return (0);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = s[i];
	return (cpy);
}
