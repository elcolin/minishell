/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:36:31 by ecolin            #+#    #+#             */
/*   Updated: 2022/11/17 22:50:29 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_invalid(char *input, int end)
{
	int	i;

	i = 0;
	if ((input[0] <= '9' && input[0] >= '0') || input[0] == '=')
	{
		ft_putstr_fd("Not a valid identifier\n", 2);
		return (1);
	}
	while (input[i])
	{
		if (end != 0)
			if (i == end)
				return (0);
		if (!is_num(input[i]) && !is_letter(input[i]) && input[i] != '_')
		{
			ft_putstr_fd("Not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	push_export(char *s, t_env *env, char *clean, char *name)
{
	t_env	*env_tmp;
	char	*value;

	env_tmp = env;
	value = export_value(s);
	while (env_tmp)
	{
		if (ft_strcmp(name, env_tmp->name) == 0)
		{
			env_tmp->value = value;
			env_tmp->line = clean;
			break ;
		}
		env_tmp = env_tmp->next;
	}
	if (!env_tmp)
		env = ft_env_push_back(env, clean, name, value);
}

int	export_parse_and_push(char **input, int i, t_env *env)
{
	int		y;
	char	*input_clean;
	char	*name;

	y = 0;
	input_clean = no_more_quotes(input[i]);
	while (input_clean[y] && input_clean[y] != '=')
		y++;
	if (is_invalid(input_clean, y))
		return (1);
	if (input_clean[y] != '=')
		return (0);
	name = ft_substr(input_clean, 0, y);
	y = 0;
	while (input[i][y] != '=')
		y++;
	push_export(input[i], env, input_clean, name);
	return (0);
}

int	export(char **input, t_env *env)
{
	int		i;
	int		return_v;

	i = 0;
	return_v = 0;
	while (input[i])
	{
		if (export_parse_and_push(input, i, env) == 1)
			return_v = 1;
		i++;
	}
	return (return_v);
}

int	unset(char **input, t_env *env)
{
	int		i;
	int		return_v;
	t_env	*env_tmp;

	i = 0;
	return_v = 0;
	while (input[i])
	{
		env_tmp = env;
		if (ft_strcmp(input[i], env->name) == 0)
			*env = *env->next;
		while (env_tmp && env_tmp->next)
		{
			if (is_invalid(input[i], 0))
			{
				return_v = 1;
				break ;
			}
			if (ft_strcmp(input[i], env_tmp->next->name) == 0)
				env_tmp->next = env_tmp->next->next;
			env_tmp = env_tmp->next;
		}
		i++;
	}
	return (return_v);
}
