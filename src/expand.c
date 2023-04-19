/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:32:51 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/20 15:22:56 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_index(char *arg)
{
	int	i;

	i = 0;
	while ((arg[i] != '$' && arg[i])
		|| (arg[i] == '$' && arg[i + 1] && (arg[i + 1] == ' '
				|| arg[i + 1] == '"' || arg[i + 1] == '\''
				|| arg[i + 1] == '=' || arg[i + 1] == ':')))
		i++;
	return (i);
}

char	*expand_replace(char *tmp, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
		{
			j = strchri(&tmp[i + 1], tmp[i]);
			if (j != -1)
				i += j + 1;
		}
		if (tmp[i] == '$')
		{
			tmp = expand(tmp, env, 1);
			break ;
		}
		i++;
	}
	return (tmp);
}

char	*_before_expand(char *before_expand, char *arg, int i)
{
	before_expand[i] = '\0';
	while (i > 0)
	{
		i--;
		before_expand[i] = arg[i];
	}
	return (before_expand);
}

char	*expand(char *arg, t_env *env, int inside)
{
	char	*before_expand;
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	if (!arg)
		return (0);
	i = expand_index(arg);
	if (i + 1 == (int) ft_strlen(arg) || i == (int) ft_strlen(arg))
		return (arg);
	before_expand = ft_malloc(i + 1);
	before_expand = _before_expand(before_expand, arg, i);
	y = i;
	while (y--)
		arg++;
	arg++;
	if (inside)
		tmp = ft_strjoin(before_expand, no_more_quotes(after(arg, env)));
	else
		tmp = ft_strjoin(before_expand, after(arg, env));
	return (expand_replace(tmp, env));
}
