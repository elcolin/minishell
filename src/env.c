/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenayou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:45:18 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/17 20:47:23 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	int		y;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		y = 0;
		while (envp[i][y] != '=')
			y++;
		env = ft_env_push_back(env, envp[i], ft_substr(envp[i], 0, y),
				ft_substr(envp[i], y + 1, ft_strlen(envp[i])));
		if (env == NULL)
			return (NULL);
		i++;
	}
	return (env);
}

int	_env(t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		printf("%s\n", env_tmp->line);
		env_tmp = env_tmp->next;
	}
	return (0);
}
