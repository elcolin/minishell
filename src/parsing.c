/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:31:00 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/20 15:43:06 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_res(t_input *head, char *s, int *q, t_env *env)
{
	char	*res;

	res = 0;
	if (add_who_next(&head, 0, 0) && (add_who_next(&head, 0, 0)->type != PIPE
			&& add_who_next(&head, 0, 0)->type
			&& add_who_next(&head, 0, 0)->type != CAT))
		res = expand(s, env, 0);
	else
	{
		res = no_more_quotes(expand(s, env, 0));
		if (ft_strcmp(s, res))
			(*q) = 1;
	}
	return (res);
}

char	*single_expand(char *s, t_env *env, int *q, t_input *head)
{
	int		i;
	int		k;
	char	*res;

	res = 0;
	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			res = ft_strjoin(res, got_quotes(s, &i, &k, env));
		i++;
	}
	if (i != k && res)
		res = ft_strjoin(res, dup_expand(&s[k], i - k, env));
	if (!res)
		res = get_res(head, s, q, env);
	return (res);
}

t_input	*split_to_list(char *s, t_root *root)
{
	t_input	*head;
	char	*tmp;
	int		i;
	int		j;
	int		q;

	head = 0;
	i = 0;
	while (s[i])
	{
		q = 0;
		i += count_char(&s[i], ' ');
		j = arg(&s[i]);
		if (!j)
			return (head);
		tmp = ft_strndup(&s[i], j);
		i += j;
		if (tmp && !(head && add_who_next(&head, 0, 0)->type == CAT))
			tmp = add_arg(&head, single_expand(tmp, root->env, &q, head), q);
		if (tmp && tmp[0] && !q)
			add_who_next(&head, no_more_quotes(tmp), q);
		else if (tmp && tmp[0])
			add_who_next(&head, ft_strdup(tmp), q);
	}
	return (head);
}

t_input	*parsing(char *s, t_root *root)
{
	t_input	*index;

	if (!s)
	{
		free_garbage();
		ft_putstr_fd("exit\n", 2);
		exit(message_error(0, 1, 0));
	}
	if (s[0])
		add_history(s);
	root->parse = split_to_list(s, root);
	index = root->parse;
	if (root->parse && root->parse->type == PIPE)
		return (message_error(2, 0, 1), NULL);
	while (index)
	{
		if ((index->type && !index->next) || (index->type
				&& index->next && index->next->type == index->type)
			|| (index->type && index->type != PIPE
				&& index->next && index->next->type))
			return (message_error(2, 0, 1), NULL);
		index = index->next;
	}
	free(s);
	return (root->parse);
}
