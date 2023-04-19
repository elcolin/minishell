/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:21:17 by elise             #+#    #+#             */
/*   Updated: 2022/11/20 17:06:23 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirection(t_cmd	*cmd)
{
	t_input	*index;
	int		fdin;
	int		fdout;

	fdin = 0;
	fdout = 0;
	index = cmd->init_input;
	while (index && index->type != PIPE)
	{
		if (open_fd(index, &fdin, &fdout))
			return (message_error(errno, 0, 1));
		if (fdin)
		{
			close_init(&cmd->infile);
			cmd->infile = fdin;
		}
		if (fdout)
		{
			close_init(&cmd->outfile);
			cmd->outfile = fdout;
		}
		index = index->next;
	}
	return (0);
}

int	open_fd(t_input *index, int *fdin, int *fdout)
{
	*fdin = 0;
	*fdout = 0;
	if (!index->next)
		return (0);
	if (index->type == REDIRECT_STDIN && index->next)
		*fdin = open(index->next->input, O_RDONLY);
	else if (index->type == REDIRECT_STDOUT && index->next)
		*fdout = open(index->next->input, O_CREAT
				| O_TRUNC | O_WRONLY, 0000644);
	else if (index->type == APPEND && index->next)
		*fdout = open(index->next->input, O_CREAT
				| O_WRONLY | O_APPEND, 0000644);
	else if (index->type == CAT && index->next)
		*fdin = open("/tmp/.tmp", O_RDONLY);
	if (*fdin < 0)
		return (message_error(errno, 0, 0));
	else if (*fdout < 0)
		return (message_error(errno, 0, 0));
	return (0);
}

int	no_cmd(t_input *parse)
{
	t_input	*index;
	int		fdin;
	int		fdout;

	fdin = 0;
	fdout = 0;
	index = parse;
	if (!parse || *_heredoc_sigint() == 1)
		return (0);
	while (index)
	{
		if (open_fd(index, &fdin, &fdout))
			return (message_error(errno, 0, 1));
		close_init(&fdin);
		close_init(&fdout);
		index = index->next;
	}
	return (0);
}

int	get_fdout(t_root	*root, int *fdout, t_cmd *index)
{
	if (redirection(index))
		return (1);
	if (find_pipe(index->cmd_input))
		err(pipe(root->pipefd), root);
	if (index->outfile)
	{
		(*fdout) = index->outfile;
		if (find_pipe(index->cmd_input))
			close_init(&root->pipefd[1]);
	}
	else if (!index->outfile)
	{
		if (find_pipe(index->cmd_input))
		{
			(*fdout) = root->pipefd[1];
			index->close = root->pipefd[0];
		}
		else
			err((*fdout) = dup(root->outfile), root);
	}
	err(dup2((*fdout), 1), root);
	err(close_init(&(*fdout)), root);
	return (0);
}

int	get_fdin(t_root *root, int *fdin, t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (redirection(cmd))
		return (1);
	if (cmd->infile)
	{
		(*fdin) = cmd->infile;
		if (previous_pipe(root->parse, cmd->init_input))
			close_init(&root->pipefd[0]);
	}
	else if (!cmd->infile)
	{
		if (previous_pipe(root->parse, cmd->init_input))
		{
			if (!root->pipefd[0])
				err(pipe(root->pipefd), root);
			(*fdin) = root->pipefd[0];
			close_init(&root->pipefd[1]);
		}
		else
			err((*fdin) = dup(root->infile), root);
	}
	err(dup2((*fdin), 0), root);
	err(close_init(&(*fdin)), root);
	return (0);
}
