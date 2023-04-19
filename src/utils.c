/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenayou <rbenayou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:37:35 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/17 20:42:53 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_num(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	is_letter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

t_env	*ft_create_node(char *line, char *name, char *value)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->line = line;
	node->name = name;
	node->value = value;
	return (node);
}

t_env	*ft_env_push_back(t_env *list, char *line, char *name, char *value)
{
	t_env	*tmp;

	tmp = list;
	if (value == NULL || name == NULL)
		return (NULL);
	if (!list)
		return (ft_create_node(line, name, value));
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_create_node(line, name, value);
		if (tmp->next == NULL)
			return (NULL);
		return (list);
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	cpy = ft_malloc(len + 1);
	if (cpy == NULL)
		return (NULL);
	while (i < len && i + start < ft_strlen(s))
	{
		cpy[i] = s[start + i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
