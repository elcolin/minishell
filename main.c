/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:07:25 by ecolin            #+#    #+#             */
/*   Updated: 2022/10/18 12:57:16 by elise            ###   ########.fr       */
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
	new->next = NULL;
	return (new);
}

int n_occurencies(char *s, char c, int n)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while(s[i] && i < n)
	{
		if (s[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

int	arg(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			j = strchri(&s[i + 1], s[i]);
			if (j != -1)
			{
				s[i] = -1;
				s[i + j + 1] = -1;
				i += j;
			}
		}
		else if (s[i] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

t_input	*split_to_list(char *s)//gere l'apparition de quote
{
	t_input	*head;
	t_input	*new;
	char	*tmp;
	int		i;
	int		j;

	head = 0;
	i = 0;
	new = 0;
	while(s[i])
	{
		j = 0;
		while (s[i] == ' ' && s[i])
			i++;
		j = arg(&s[i]);
		if (!j)
			return (head);
		if (j == -1)
			j = ft_strlen(&s[i]);
		tmp = ft_strndup(&s[i], j);
		if (!head && tmp)
		{
			head = new_input(tmp);
			new = head;
		}
		else if (tmp)
		{
			new->next = new_input(tmp);
			new = new->next;
		}
		i += j;
	}
	return (head);
}

t_input	*parsing(char *s)
{
	t_input	*parse;
	
	add_history(s);
	parse = split_to_list(s);
	while (parse)
	{
		printf("%s\n", parse->input);
		parse = parse->next;
	}
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