/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:26:54 by elise             #+#    #+#             */
/*   Updated: 2022/11/20 00:17:16 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_input	*heredoc(t_input *input)
{
	t_input	*index;
	t_input	*sep;
	t_input	*tmp;

	index = next_type(input);
	sep = 0;
	tmp = 0;
	while (index)
	{
		if (index->type == CAT && index->next)
		{
			index = index->next;
			if (!sep)
				sep = new_input(index->input, 0);
			else
			{
				if (!tmp)
					tmp = sep;
				tmp->next = new_input(index->input, 0);
				tmp = tmp->next;
			}
		}
		index = next_type(index->next);
	}
	return (sep);
}

int	get_tmp_fd(int f_close)
{
	int	tmp_fd;

	tmp_fd = 0;
	tmp_fd = open("/tmp/.tmp", O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	if (tmp_fd < 0)
		return (message_error(ENOENT, 0, 1));
	if (f_close)
		close(tmp_fd);
	return (tmp_fd);
}

void	child(t_root *root, int tmp_fd, t_input *sep)
{
	char	*s;

	s = 0;
	while (!root->pid)
	{
		s = readline("> ");
		if (!s || (!ft_strcmp(s, sep->input) && !sep->next))
		{
			close(tmp_fd);
			free_garbage();
			if (s)
				free(s);
			exit(0);
		}
		if (!ft_strcmp(s, sep->input) && sep->next)
			sep = sep->next;
		else if (!sep->next)
			ft_putendl_fd(s, tmp_fd);
		free(s);
	}
}

int	input_heredoc(t_input	*sep, t_root *root)
{
	int		tmp_fd;
	int		status;

	status = 0;
	tmp_fd = get_tmp_fd(0);
	root->pid = fork();
	signal(SIGINT, handler_heredoc);
	child(root, tmp_fd, sep);
	signal(SIGINT, SIG_IGN);
	waitpid(0, &status, 0);
	close(tmp_fd);
	status = exit_signal(status);
	if (status == 130)
		*_heredoc_sigint() = 1;
	if (status)
	{
		tmp_fd = get_tmp_fd(1);
		return (message_error(status, 0, 0));
	}
	return (0);
}
