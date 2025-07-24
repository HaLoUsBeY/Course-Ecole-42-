/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rot_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:26:13 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/27 14:44:15 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	reverse_rotate(t_data **stack)
{
	t_data	*first;
	t_data	*last;
	t_data	*prev;

	if (stack_len(*stack) < 2)
		return ;
	first = *stack;
	last = *stack;
	prev = NULL;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	last->next = first;
	prev->next = NULL;
	*stack = last;
}

void	reverse_rotate_a(t_data **stack_a)
{
	reverse_rotate(stack_a);
	ft_printf("rra\n");
}

void	reverse_rotate_b(t_data **stack_b)
{
	reverse_rotate(stack_b);
	ft_printf("rrb\n");
}
