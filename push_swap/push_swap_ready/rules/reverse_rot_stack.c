/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rot_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:26:13 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/26 15:06:51 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	reverse_rotate(p_data **stack)
{
	p_data	*first;
	p_data	*last;
	p_data	*prev;

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

void	reverse_rotate_a(p_data **stack_a)
{
	reverse_rotate(stack_a);
	ft_printf("rra\n");
}

void	reverse_rotate_b(p_data **stack_b)
{
	reverse_rotate(stack_b);
	ft_printf("rrb\n");
}