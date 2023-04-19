/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:35:31 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/20 17:07:14 by ecolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/minishell.h"

int	echo_print(char **input, int i, int n);
int	echo(char **input);

int	echo(char **input)
{
	int	i;
	int	y;
	int	n;

	i = 0;
	n = 0;
	if (input[i] && input[i][0] == '-')
	{
		while (input[i] && input[i][0] == '-')
		{
			y = 1;
			if (!input[i][y])
				break ;
			while (input[i][y] == 'n')
				y++;
			if (input[i][y])
				break ;
			n = 1;
			i++;
		}
	}
	return (echo_print(input, i, n));
}

int	echo_print(char **input, int i, int n)
{
	if (!input[i] && n == 0)
		ft_putchar_fd('\n', 1);
	while (input[i] && input[i + 1])
	{
		ft_putstr_fd(input[i++], 1);
		ft_putchar_fd(' ', 1);
	}
	if (input[i] && n == 0)
	{
		ft_putstr_fd(input[i], 1);
		ft_putchar_fd('\n', 1);
	}
	else if (input[i] && n == 1)
		ft_putstr_fd(input[i], 1);
	return (0);
}
