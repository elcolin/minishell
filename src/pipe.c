/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:10:57 by elise             #+#    #+#             */
/*   Updated: 2022/11/20 16:41:52 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_cmd *cmd, t_root *root)
{
	int	value;

	value = -1;
	if ((!cmd || !cmd->parse_cmd))
		return (-1);
	if (!ft_strcmp(cmd->parse_cmd[0], "cd"))
		value = message_error(cd(&cmd->parse_cmd[1], root->env), 0, 0);
	else if (!ft_strcmp(cmd->parse_cmd[0], "export"))
		value = message_error(export(&cmd->parse_cmd[1], root->env), 0, 0);
	else if (!ft_strcmp(cmd->parse_cmd[0], "unset"))
		value = message_error(unset(&cmd->parse_cmd[1], root->env), 0, 0);
	else if (!ft_strcmp(cmd->parse_cmd[0], "env"))
		value = message_error(_env(root->env), 0, 0);
	else if (!ft_strcmp(cmd->parse_cmd[0], "pwd"))
		value = message_error(pwd(), 0, 0);
	else if (!ft_strcmp(cmd->parse_cmd[0], "echo"))
		value = message_error(echo(&cmd->parse_cmd[1]), 0, 0);
	else if (!ft_strcmp(cmd->parse_cmd[0], "exit") && !cmd->pid)
		value = message_error(b_exit(&cmd->parse_cmd[1], 0), 0, 0);
	else if (!ft_strcmp(cmd->parse_cmd[0], "exit") && cmd->pid)
		value = message_error(b_exit(&cmd->parse_cmd[1], 1), 0, 0);
	if (root->cmd_num > 1 && value != -1)
		free_garbage();
	return (value);
}

int	exec_cmd(t_root *root, t_cmd *cmd)
{
	int	status;

	if (root->cmd_num == 1)
	{
		close_init(&cmd->close);
		status = is_builtin(cmd, root);
		if (root->exit)
			return (stop_exec(message_error(0, 1, 0), root, 0, 1));
		if (status != -1)
			return (message_error(status, 0, 0));
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (stop_exec(errno, root, 1, 1));
	else if (!cmd->pid)
	{
		close_init(&cmd->close);
		status = is_builtin(cmd, root);
		if (status == -1)
			err(execve(cmd->cmd, cmd->parse_cmd, root->envp), root);
		exit(status);
	}
	return (-1);
}

int	pipe_exec(t_cmd *index, t_root *root)
{
	int	b_status;

	b_status = exec_cmd(root, index);
	if (!index->next_cmd && find_pipe(index->cmd_input))
		b_status = 127;
	if (find_pipe(index->cmd_input) && !cmd_is_next_input(index))
	{
		close_init(&root->pipefd[0]);
		err(pipe(root->pipefd), root);
		close_init(&root->pipefd[1]);
	}
	return (b_status);
}

int	wait_for_child(t_root *root)
{
	int		status;
	t_cmd	*index;

	status = 0;
	index = root->cmd_lst;
	while (index)
	{
		stop_exec(0, root, 0, 0);
		signal(SIGINT, handler_cmd);
		waitpid(index->pid, &status, 0);
		if (status == 130)
			kill(0, SIGINT);
		index = index->next_cmd;
	}
	return (status);
}

int	exec(t_root *root)
{
	int		fdin;
	int		fdout;
	int		b_status;
	t_cmd	*index;

	root->infile = dup(0);
	root->outfile = dup(1);
	fdin = 0;
	fdout = 0;
	b_status = -1;
	index = root->cmd_lst;
	while (index)
	{
		if (get_fdin(root, &fdin, index))
			return (stop_exec(1, root, 0, 0));
		if (get_fdout(root, &fdout, index))
			return (stop_exec(1, root, 0, 0));
		b_status = pipe_exec(index, root);
		index = index->next_cmd;
	}
	return (exit_status(wait_for_child(root), b_status, root));
}
