/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:19:38 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/20 16:42:13 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	message_error(int err, int last, int print)
{
	static int	last_err;

	if (last)
		return (last_err);
	if (err == 0)
		return (last_err = 0);
	else if (err == 127 && print)
	{
		ft_putstr_fd("Command not found\n", 2);
		return (last_err = 127);
	}
	else if (err == 2 && print)
	{
		ft_putstr_fd("Syntax error near token\n", 2);
		return (last_err = 2);
	}
	else if ((errno || err) && print)
		perror(strerror(err));
	if (err == 13)
		err = 126;
	last_err = err;
	return (last_err);
}

int	exit_signal(int status)
{
	if (*_heredoc_sigint())
		return (0);
	if (WIFEXITED(status))
		return (message_error(WEXITSTATUS(status), 0, 0));
	else if (WIFSIGNALED(status))
		return (message_error(WTERMSIG(status) + 128, 0, 0));
	else if (WIFSTOPPED(status))
		return (message_error(WSTOPSIG(status), 0, 0));
	else
		return (0);
}

void	err(int value, t_root	*root)
{
	if (value == -1)
		stop_exec(errno, root, 1, 1);
}

int	exit_status(int status, int b_status, t_root *root)
{
	if (exit_signal(status) && b_status != 127)
	{
		close_init(&root->pipefd[1]);
		return (exit_signal(status));
	}
	if (b_status == -1)
		return (stop_exec(WEXITSTATUS(status), root, 0, 0));
	return (stop_exec(b_status, root, 0, 0));
}

int	stop_exec(int err, t_root *root, int print, int exit)
{
	dup2(root->infile, 0);
	dup2(root->outfile, 1);
	close_init(&root->infile);
	close_init(&root->outfile);
	if (exit)
	{
		message_error(err, 0, print);
		b_exit(0, 0);
	}
	if (err)
		return (message_error(err, 0, print));
	return (message_error(err, 1, print));
}
