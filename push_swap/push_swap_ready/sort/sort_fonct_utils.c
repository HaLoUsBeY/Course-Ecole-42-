/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fonct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:26:33 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/26 15:50:58 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_min_value(p_data **a_stack)
{
	int		min_value;
	int		min_tab;
	int		tab;
	p_data	*node;

	tab = 0;
	min_tab = 0;
	node = *a_stack;
	min_value = node->data;
	while (node)
	{
		if (node->data < min_value)
		{
			min_value = node->data;
			min_tab = tab;
		}
		node = node->next;
		tab++;
	}
	return (min_tab);
}

void	lurk_middle(p_data **a_stack, int min_tab)
{
	int	size;

	size = stack_len(*a_stack);
	if (min_tab <= size / 2)
	{
		while (min_tab-- > 0)
			sortexe(a_stack, NULL, ROTATE_A);
	}
	else
	{
		min_tab = size - min_tab;
		while (min_tab-- > 0)
			sortexe(a_stack, NULL, REVERSE_ROTATE_A);
	}
}
