/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:02:44 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/20 17:07:24 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*t_zero_type(t_input **t, t_input **init_input,
	t_input **cmd_input, t_root *root)
{
	char	*tmp;

	tmp = 0;
	if ((*t)->input)
		tmp = is_cmd(root, (*t)->input);
	if (!tmp)
	{
		(*cmd_input) = 0;
		while ((*t) && (*t)->type != PIPE)
			(*t) = (*t)->next;
		if (*t)
			(*init_input) = (*t)->next;
	}
	else
		(*cmd_input) = (*t);
	return (tmp);
}

char	*t_has_type(t_input **t, t_input **init_input)
{
	if ((*t)->type != PIPE)
	{
		if ((*t)->next)
			(*t) = (*t)->next->next;
	}
	else
	{
		(*t) = (*t)->next;
		(*init_input) = (*t);
	}
	return (0);
}

void	str_exists(char *tmp, t_input **t, t_input **init_input)
{
	if (tmp)
	{
		while (*t && (*t)->type != PIPE)
			*t = (*t)->next;
		if (*t)
			(*init_input) = (*t)->next;
	}
}

char	**parsing_cmd(char *cmd, t_input *parse)
{
	char	**parse_cmd;
	t_input	*root_parse;
	int		i;

	i = 0;
	parse_cmd = 0;
	root_parse = parse;
	if (!cmd)
		return (0);
	i = how_big(parse);
	parse_cmd = ft_malloc(sizeof(char *) * (i + 1));
	parse_cmd[i] = 0;
	parse = root_parse;
	i = 0;
	while (parse && parse->type != PIPE)
	{
		if (!parse->type)
			parse_cmd[i++] = parse->input;
		else if (parse->next)
			parse = parse->next;
		parse = parse->next;
	}
	return (parse_cmd);
}

char	*is_cmd(t_root *root, char *input)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_strcmp(input, "cd") || !ft_strcmp(input, "export")
		|| !ft_strcmp(input, "unset") || !ft_strcmp(input, "env")
		|| !ft_strcmp(input, "echo") || !ft_strcmp(input, "exit"))
		return (input);
	if (!root->path || ft_strchr(input, '/'))
	{
		if (!access(input, X_OK))
			return (input);
		return (message_error(127, 0, 1), NULL);
	}
	tmp = ft_strjoin("/", input);
	if (!tmp)
		return (0);
	while (root->path[i])
	{
		input = ft_strjoin(root->path[i++], tmp);
		if (!access(input, X_OK))
			return (input);
	}
	return (message_error(127, 0, 1), NULL);
}
