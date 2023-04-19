/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenayou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:35:36 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/17 20:37:20 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *name, t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strcmp(name, env_tmp->name) == 0)
			return (env_tmp->value);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

char	*cut_arg(char *arg, int y)
{
	int		end;
	int		x;
	char	*cut_part;

	end = ft_strlen(arg) - y;
	cut_part = ft_malloc(end + 2);
	x = 0;
	while (x <= end)
	{
		cut_part[x] = arg[y];
		y++;
		x++;
	}
	cut_part[x] = '\0';
	return (cut_part);
}

int	after_index(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '?' || is_num(arg[i]))
		i++;
	else
	{
		while (is_num(arg[i]) || is_letter(arg[i]) || arg[i] == '_')
			i++;
	}
	return (i);
}

char	*after(char *arg, t_env *env)
{
	int		i;
	char	*real_arg;
	char	*cut_part;

	i = after_index(arg);
	real_arg = ft_malloc(i + 1);
	cut_part = cut_arg(arg, i);
	real_arg[i] = '\0';
	while (i > 0)
	{
		i--;
		real_arg[i] = arg[i];
	}
	if (arg[0] == '?')
		return (ft_strjoin(ft_itoa(message_error(0, 1, 0)), cut_part));
	if (ft_getenv(real_arg, env) == NULL)
	{
		if (!cut_part[0])
			cut_part[0] = '\0';
		return (cut_part);
	}
	return (ft_strjoin(ft_getenv(real_arg, env), cut_part));
}
