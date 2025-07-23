/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:27:38 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/26 15:06:54 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	rotate(p_data **stack)
{
	p_data	*first;
	p_data	*last;

	if (stack_len(*stack) < 2)
		return ;
	first = *stack;
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = first;
	*stack = first->next;
	first->next = NULL;
}

void	rotate_a(p_data **stack_a)
{
	rotate(stack_a);
	ft_printf("ra\n");
}

void	rotate_b(p_data **stack_b)
{
	rotate(stack_b);
	ft_printf("rb\n");
}