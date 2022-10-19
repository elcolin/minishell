/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:07:25 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/19 15:34:18 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strchri(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}


int main(int argc, char *argv[], char **env)
{
	t_root	root;
	t_input	*parse;

	while (1)
	{
		parse = parsing(readline("minishell> "));
	}
	/*char	*prompt;

	// while ()
	prompt = readline("A new fancy line! Whatcha say?\nminishell> ");
	check_arg(prompt);
	add_history(prompt);
	// printf("Did you say \"%s\"?\n", prompt);
	while (ft_strncmp(prompt, "exit(", 5))
	{
		free(prompt);
		prompt = readline("minishell> ");
		check_arg(prompt);
		add_history(prompt);
	}*/
}