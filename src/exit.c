/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:51:56 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/20 16:59:33 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_num_err(int print)
{
	if (print)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Numeric argument required\n", 2);
	free_garbage();
	exit(2);
}

void	valid_exit(char **input, int print)
{
	int		y;

	y = 0;
	if (input[0])
	{	
		if (input[0][0] == '+' || input[0][0] == '-' || is_num(input[0][0]))
			y = 1;
		else
			exit_num_err(print);
		while (input[0][y])
		{
			if (is_num(input[0][y]))
				y++;
			else
				exit_num_err(print);
		}
	}
}

void	exit_atoi(char *input, int print)
{
	long	i;

	i = ft_atoi(input);
	free_garbage();
	if (print)
		ft_putstr_fd("exit\n", 2);
	exit(i);
}

int	b_exit(char **input, int print)
{
	if (!input)
	{
		free_garbage();
		exit(message_error(0, 1, 0));
	}
	if ((input && !input[0]))
	{
		if (print)
			ft_putstr_fd("exit\n", 2);
		free_garbage();
		exit(message_error(0, 1, 0));
	}
	valid_exit(input, print);
	if (input[0] && input[1])
	{
		if (print)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("Too many arguments\n", 2);
		return (1);
	}
	exit_atoi(input[0], print);
	return (0);
}

int	close_init(int	*fd)
{
	if (*fd > 0)
	{
		if (close(*fd) < 0)
			return (-1);
		(*fd) = 0;
	}
	return (0);
}
