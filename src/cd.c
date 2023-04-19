/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenayou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:48:59 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/17 21:25:09 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = ft_malloc(sizeof(char) * PATH_MAX);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_putstr_fd("Error with PWD\n", 2);
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}

int	access_path(char **path, t_env *env)
{
	if (!path[0])
	{
		if (ft_getenv("HOME", env) != NULL)
		{
			if (chdir(ft_getenv("HOME", env)) != 0)
				return (1);
		}
		else
		{
			ft_putstr_fd("HOME not set\n", 2);
			return (1);
		}
	}
	else
	{
		if (chdir(path[0]) != 0)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}

char	**init_for_expand(char *cwd, char *name)
{
	char	**s;

	s = ft_malloc(sizeof(s) * 2);
	s[0] = ft_strjoin(name, cwd);
	s[1] = NULL;
	return (s);
}

int	cd_error(char *s)
{
	ft_putstr_fd(s, 2);
	return (1);
}

int	cd(char **path, t_env *env)
{
	char	*cwd;
	char	**oldpwd;
	char	**pwd;

	if (path[0] && path[1])
		return (cd_error("Too many arguments\n"));
	cwd = ft_malloc(sizeof(char) * PATH_MAX);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (cd_error("cd : Error with PWD\n"));
	oldpwd = init_for_expand(cwd, "OLDPWD=");
	if (access_path(path, env))
		return (1);
	cwd = ft_malloc(sizeof(char) * PATH_MAX);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (cd_error("cd : Error with PWD\n"));
	pwd = init_for_expand(cwd, "PWD=");
	export(oldpwd, env);
	export(pwd, env);
	return (0);
}
