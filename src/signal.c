/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:47:45 by elise             #+#    #+#             */
/*   Updated: 2022/11/20 14:44:24 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_prompt(int sig)
{
	if (sig == 2)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 2);
		rl_redisplay();
		message_error(130, 0, 0);
	}
}

void	handler_cmd(int sig)
{
	(void) sig;
	write(1, "\n", 2);
	message_error(130, 0, 0);
	*_heredoc_sigint() = 1;
	return ;
}

void	handler_heredoc(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	close(*_heredoc_sigint());
	free_garbage();
	exit(130);
	*_heredoc_sigint() = 1;
	return ;
}

void	sig_init(struct sigaction *sa_prompt)
{
	struct sigaction	sa_sigquit;

	sa_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_flags = 0;
	sa_prompt->sa_handler = &handler_prompt;
	sigemptyset(&sa_prompt->sa_mask);
	sa_prompt->sa_flags = 0;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
