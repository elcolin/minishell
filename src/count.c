/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:50:31 by elise             #+#    #+#             */
/*   Updated: 2022/11/19 01:48:29 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	command_number(t_input *input)
{
	int	i;

	i = 0;
	if (input)
		i++;
	while (input)
	{
		if (input->type == PIPE)
			i++;
		input = input->next;
	}
	return (i);
}

int	how_big(t_input	*parse)
{
	int	i;

	i = 0;
	while (parse && parse->type != PIPE)
	{
		if (!parse->type)
			i++;
		else if (parse->type && parse->next)
			parse = parse->next;
		parse = parse->next;
	}
	return (i);
}
