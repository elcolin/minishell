/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:34:48 by elise             #+#    #+#             */
/*   Updated: 2022/11/20 00:44:57 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_input	*new_input(char *s, int no_type)
{
	t_input	*new;

	new = ft_malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->input = s;
	new->next = NULL;
	if (!no_type)
		new->type = get_type(s);
	else
		new->type = 0;
	return (new);
}

t_input	*add_who_next(t_input **head, char *s, int no_type)
{
	t_input	*new;

	new = (*head);
	if (!s && !(*head))
		return (0);
	else if (!s)
	{
		while (new->next)
			new = new->next;
	}
	else if (!(*head))
	{
		(*head) = new_input(s, no_type);
		new = (*head);
	}
	else
	{
		while (new->next)
			new = new->next;
		new->next = new_input(s, no_type);
		new = new->next;
	}
	return (new);
}

t_cmd	*new_cmd(char *cmd, t_input *init_input,
	t_input *cmd_input, t_input *parse)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->parse_cmd = parsing_cmd(cmd, parse);
	if (!new->parse_cmd)
		return (0);
	new->init_input = init_input;
	new->cmd = cmd;
	new->infile = 0;
	new->outfile = 0;
	new->next_cmd = 0;
	new->close = 0;
	new->cmd_input = cmd_input;
	new->pid = 1;
	return (new);
}

void	command_list(t_input	*parse, t_root *root)
{
	t_cmd	*cmd;
	char	*tmp;
	t_input	*temp;
	t_input	*cmd_input;

	temp = parse;
	cmd_input = 0;
	cmd = 0;
	while (parse)
	{
		if (!parse->type)
			tmp = t_zero_type(&parse, &temp, &cmd_input, root);
		else
			tmp = t_has_type(&parse, &temp);
		if (!root->cmd_lst && tmp)
			root->cmd_lst = new_cmd(tmp, temp, cmd_input, parse);
		else if (tmp)
		{
			if (!cmd)
				cmd = root->cmd_lst;
			cmd->next_cmd = new_cmd(tmp, temp, cmd_input, parse);
			cmd = cmd->next_cmd;
		}
		str_exists(tmp, &parse, &temp);
	}
}
