/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:02:55 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/17 02:16:21 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/minishell.h"

size_t	l_size(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			while (s[i] == c && s[i])
				i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	if (!s)
		return (0);
	dst = ft_malloc(((k = l_size(s, c)) + 1) * sizeof(char *));
	dst[k] = 0;
	while (*s)
	{
		i = 0;
		while (s[i] != c && s[i])
			i++;
		if (i > 0 && j < k)
		{
			dst[j] = ft_malloc(i + 1);
			ft_strlcpy(dst[j++], ((char *) s), i + 1);
		}
		s += i;
		if (*(s))
			s++;
	}
	return (dst);
}
