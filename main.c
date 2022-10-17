/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:07:25 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/17 17:50:37 by ecolin           ###   ########.fr       */
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

t_input	*new_input(char *s)
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->input = s;
	new->next = 0;
}

t_input	*split_to_list(char *s)//ne gere pas l'apparition des quotes
{
	t_input	*head;
	t_input	*new;
	int	i;
	int	j;
	int	quote;
	int quote_nb;

	head = NULL;
	i = 0;
	j = 0;
	quote = 0;
	quote_nb = 0;
	while(s[i])
	{
		j = 0;
		while (s[i] == ' ' && s[i])
			i++;
		while (((s[i + j] != ' ') || (quote && quote != -1)) && s[i + j])
		{
			if ((s[i + j] == '\'' || s[i + j] == '"') && !quote && quote != -1)
			{
				quote = s[i + j];
				quote_nb++;
			}
			else if ((s[i + j] == quote) && quote && quote != -1)
			{
				quote = 0;
				quote_nb++;
			}
			printf("%d\n", quote);
			j++;
			if (!s[i + j] && (quote != -1 && quote) && quote_nb < 2)
			{
				j = 0;
				quote = -1;
			}
		}
		printf("%d\n", quote);
		quote = 0;
		if (!j)
			return (head);
		if (!head)
		{
			head = new_input(ft_strndup(&s[i], j));
			new = head;
		}
		else
			new->next = new_input(ft_strndup(&s[i], j));
		if (new->next)
			new = new->next;
		i += j;
	}
	return (head);
}

t_input	*parsing(char *s)
{
	t_input	*parse;
	
	parse = split_to_list(s);
	while (parse)
	{
		printf("%s\n", parse->input);
		parse = parse->next;
	}
	add_history(s);
	free(s);
	return (parse);
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