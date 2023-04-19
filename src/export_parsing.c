/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenayou <rbenayou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 03:16:10 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/17 19:39:38 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_strchri(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != '=')
	{
		if (s[i] == c)
			return (i);
		else if ((c == '\'' && s[i] == '"') || (c == '"' && s[i] == '\''))
		{
			ft_putstr_fd("Not a valid identifier\n", 2);
			return (-2);
		}
		i++;
	}
	return (-1);
}

int	first_eq(char *s)
{
	int	j;

	j = 0;
	while (s[j] && s[j] != '=')
		j++;
	return (j);
}

char	*modify_value(char *s, char quote)
{
	while (s && s[0] != '=')
		s++;
	s++;
	if (quote == '"')
		return (ft_strjoin("\"", s));
	if (quote == '\'')
		return (ft_strjoin("'", s));
	return (NULL);
}

char	*export_alone_quote(char *input, int i, int j)
{
	j = strchri(&input[i + 1], input[i]);
	if (j == -1)
	{
		ft_putstr_fd("Not a valid identifier\n", 2);
		return (NULL);
	}
	i += (j + 1);
	if ((i - 1) == first_eq(input))
		return (ft_substr(input, first_eq(input) + 2, ft_strlen(input)));
	return (modify_value(input, input[i]));
}

char	*export_value(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] && input[i] != '=')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = export_strchri(&input[i + 1], input[i]);
			if (j == -2)
				return (NULL);
			if (j == -1)
				break ;
			i += (j + 1);
		}
		i++;
	}
	if (j == -1)
		return (export_alone_quote(input, i, j));
	else
		return (ft_substr(input, first_eq(input) + 1, ft_strlen(input)));
}
