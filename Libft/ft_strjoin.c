/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:55:25 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/09 18:29:33 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*s;
	size_t	size1;

	size1 = ft_strlen(s1);
	size = size1 + ft_strlen(s2) + 1;
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return ((char *) s2);
	else if (!s2)
		return ((char *) s1);
	s = ft_malloc(size);
	if (!s)
		return (0);
	ft_strlcpy(s, s1, size);
	ft_strlcpy(s + size1, s2, size);
	return (s);
}
