/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:44:10 by elise             #+#    #+#             */
/*   Updated: 2022/11/19 01:03:19 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	return (i);
}

char	*skip_char(char *s, char	*c)
{
	char	**tmp;
	char	*res;
	int		i;

	i = 1;
	if (!s || !c)
		return (0);
	tmp = ft_split(s, c[0]);
	res = ft_strdup(tmp[0]);
	if (tmp[i])
			res = ft_strjoin(res, c);
	while (tmp[i])
	{
		res = ft_strjoin(res, tmp[i]);
		i++;
		if (tmp[i])
			res = ft_strjoin(res, c);
	}
	return (res);
}

char	*no_more_quotes(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(s);
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '"')
		{
			j = strchri(&tmp[i + 1], tmp[i]);
			if (j != -1)
			{
				tmp[i] = -1;
				tmp[i + j + 1] = -1;
				i += j + 1;
			}
		}
		i++;
	}
	return (ft_strndup(tmp, ft_strlen(tmp)));
}

char	**find_paths(t_env *env)
{
	while (env && ft_strcmp(env->name, "PATH"))
		env = env->next;
	if (!env || !env->value)
		return (0);
	return (ft_split(env->value, ':'));
}
