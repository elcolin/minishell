/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:21:47 by rbenayou          #+#    #+#             */
/*   Updated: 2022/11/17 18:59:33 by rbenayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "../includes/minishell.h"

void	*ft_malloc(size_t size)
{
	t_garbage	*tmp;

	tmp = push_garbage(_garbage()->garbage, malloc(size));
	if (tmp == NULL)
	{
		free_garbage();
		ft_putstr_fd("error : malloc failed\n", 2);
		exit(message_error(1, 1, 0));
		return (NULL);
	}
	_garbage()->garbage = tmp;
	return (tmp->p);
}

t_garbage	*push_garbage(t_garbage *begin_list, void *data)
{
	t_garbage	*node_tmp;

	if (data == NULL)
		return (NULL);
	node_tmp = create_node(data);
	if (node_tmp == NULL)
	{
		free(data);
		return (NULL);
	}
	if (begin_list == NULL)
		return (node_tmp);
	else
	{
		node_tmp->next = begin_list;
		return (node_tmp);
	}
}

t_garbage	*create_node(void *data)
{
	t_garbage	*node;

	node = malloc(sizeof(t_garbage));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->p = data;
	return (node);
}

void	free_garbage(void)
{
	t_garbage	*garbage;
	t_garbage	*tmp;

	garbage = _garbage()->garbage;
	tmp = NULL;
	while (garbage)
	{
		tmp = garbage->next;
		free(garbage->p);
		free(garbage);
		garbage = tmp;
	}
	return ;
}

t_data	*_garbage(void)
{
	static t_data	data;

	return (&data);
}

/*int	main()
{
	t_data *data;
	data = _garbage();
	data->garbage = NULL;
	

	free_garbage();
	return(0);
}*/
