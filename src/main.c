/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:07:25 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/20 15:23:26 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*_heredoc_sigint(void)
{
	static int	heredoc_sigint;

	return (&heredoc_sigint);
}

int	strchri(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	reset_root(t_root *root)
{
	root->cmd_lst = 0;
	root->exit = 0;
	root->infile = 0;
	root->outfile = 0;
	root->pid = 1;
	root->path = find_paths(root->env);
	root->pipefd[1] = 0;
	root->pipefd[0] = 0;
}

void	parse_and_exec(t_root *root)
{
	root->parse = parsing(readline("minishell> "), root);
	root->heredoc = heredoc(root->parse);
	if (root->heredoc)
		input_heredoc(root->heredoc, root);
	if (root->parse && *_heredoc_sigint() == 0)
		command_list(root->parse, root);
	root->cmd_num = command_number(root->parse);
	no_cmd(root->parse);
	if (root->cmd_lst && *_heredoc_sigint() == 0)
		exec(root);
}

int	main(int argc, char *argv[], char **envp)
{
	t_root				root;
	struct sigaction	sa_prompt;

	(void) argc;
	(void) argv;
	if (!isatty(0))
		exit(1);
	root.env = init_env(envp);
	root.envp = envp;
	root.exit = 0;
	sig_init(&sa_prompt);
	rl_outstream = stderr;
	while (!root.exit)
	{
		reset_root(&root);
		*_heredoc_sigint() = 0;
		sigaction(SIGINT, &sa_prompt, NULL);
		parse_and_exec(&root);
	}
	return (message_error(0, 1, 0));
}
