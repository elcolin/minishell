/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:31:00 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/19 19:12:58 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO Gerer les doubles quotes et single quote avec $... Peut etre si double, si s[i] == ? alors s[i] = -2?
//		Que faire s'il y a plusieurs $? -> n_occurencies, any_meta(char *s, int n)

int	get_type(char *str)
{
	if (!strcmp(str, "|"))
		return (PIPE);
	else if (!strcmp(str, "<"))// FAIRE FT_STRCMP
		return (REDIRECT_STDIN);
	else if (!strcmp(str, ">"))
		return (REDIRECT_STDOUT);
	else if (!strcmp(str, "<"))
		return (CAT);
	else if (!strcmp(str, ">>"))
		return (APPEND);
	else if (ft_isascii(*str))
		return (NO_SEP);
	return (-1);
}

t_input	*new_input(char *s)
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->input = s;
	new->next = NULL;
	new->type = 0;
	return (new);
}

int n_occurencies(char *s, char c, int n)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while(s[i] && i < n)
	{
		if (s[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

int	arg(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			j = strchri(&s[i + 1], s[i]);// return j tel que s[i + j] == ' ou "
			printf("%d |%c|\n", j, s[i + j]);
			if (j != -1)
			{
				s[i] = -1;
				s[i + j + 1] = -1;
				i += j + 1;
			}
		}
		if (s[i] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

t_input	*split_to_list(char *s)//gere l'apparition de quote
{
	t_input	*head;
	t_input	*new;
	char	*tmp;
	int		i;
	int		j;

	head = 0;
	i = 0;
	new = 0;
	while(s[i])
	{
		j = 0;
		while (s[i] == ' ' && s[i])
			i++;
		j = arg(&s[i]);
		if (!j)
			return (head);
		if (j == -1)
			j = ft_strlen(&s[i]);
		tmp = ft_strndup(&s[i], j);
		if (!head && tmp)
		{
			head = new_input(tmp);
			new = head;
		}
		else if (tmp)
		{
			new->next = new_input(tmp);
			new = new->next;
		}
		i += j;
	}
	return (head);
}

t_input	*parsing(char *s)
{
	t_input	*parse;
	t_input	*index;
	
	add_history(s);
	parse = split_to_list(s);
	index = parse;
	while (index)
	{
		index->type = get_type(index->input);
		index = index->next;
	}
	while (parse)
	{
		printf("%s %d\n", parse->input, parse->type);
		parse = parse->next;
	}
	free(s);
	return (parse);
}