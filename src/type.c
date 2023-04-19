/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:12:33 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/20 15:29:01 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_is_next_input(t_cmd *cmd)
{
	t_input	*input;

	if (!cmd || !cmd->next_cmd)
		return (0);
	input = cmd->cmd_input;
	cmd = cmd->next_cmd;
	while (input && input->type != PIPE)
		input = input->next;
	if (input)
		input = input->next;
	while (input && input->type != PIPE)
	{
		if (input == cmd->cmd_input)
			return (1);
		input = input->next;
	}
	return (0);
}

int	get_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, "<"))
		return (REDIRECT_STDIN);
	else if (!ft_strcmp(str, ">"))
		return (REDIRECT_STDOUT);
	else if (!ft_strcmp(str, "<<"))
		return (CAT);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND);
	else if (ft_isascii(*str))
		return (NO_SEP);
	return (-1);
}

t_input	*next_type(t_input	*input)
{
	t_input	*index;

	index = input;
	if (!input)
		return (0);
	while (index)
	{
		if (index->type)
			return (index);
		index = index->next;
	}
	return (0);
}

int	find_pipe(t_input	*input)
{
	while (input)
	{
		if (input->type == PIPE)
			return (1);
		input = input->next;
	}
	return (0);
}

int	previous_pipe(t_input *input, t_input *cmd)
{
	while (input && input != cmd)
	{
		if (input->type == PIPE)
			return (1);
		input = input->next;
	}
	return (0);
}
