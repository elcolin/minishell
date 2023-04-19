/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:41:45 by elise             #+#    #+#             */
/*   Updated: 2022/11/20 15:46:25 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dup_expand(char *s, int size, t_env *env)
{
	char	*str;

	str = 0;
	if (!s)
		return (0);
	if (size > 0 && s[size - 1] == '$')
		size --;
	str = ft_strndup(s, size);
	str = expand(str, env, 0);
	return (str);
}

int	arg(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>'))
		return (2);
	else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		return (1);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			j = strchri(&s[i + 1], s[i]);
			if (j != -1)
				i += j + 1;
		}
		if (s[i] == ' ' || s[i] == '|' || s[i] == '<' || s[i] == '>')
			return (i);
		i++;
	}
	return (ft_strlen(s));
}

char	*add_arg(t_input **head, char *tmp, int q)
{
	int	j;

	j = 0;
	if (q)
		tmp += count_char(tmp, ' ');
	j = arg(tmp);
	while (tmp && j)
	{
		if ((add_who_next(head, 0, 0)
				&& !ft_strcmp(add_who_next(head, 0, 0)->input, "export")) || q)
			add_who_next(head, ft_strndup(tmp, j), q);
		else
			add_who_next(head, no_more_quotes(ft_strndup(tmp, j)), q);
		tmp += j;
		if (q)
			tmp += count_char(tmp, ' ');
		j = arg(tmp);
	}
	return (tmp);
}

char	*got_quotes(char *s, int *i, int *k, t_env *env)
{
	int		j;
	char	*tmp2;
	char	*tmp;

	tmp = 0;
	tmp2 = 0;
	j = strchri(&s[(*i) + 1], s[*i]);
	if (j != -1)
	{
		tmp = ft_strndup(&s[*i], j + 2);
		if (s[*i] == '"' && tmp)
			tmp = expand(tmp, env, 1);
		tmp2 = dup_expand(&s[*k], (*i) - (*k), env);
		(*i) += j + 1;
		(*k) = (*i) + 1;
		return (ft_strjoin(tmp2, tmp));
	}
	return (0);
}
