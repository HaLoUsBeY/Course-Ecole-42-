/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:24:05 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/27 14:44:15 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	push(t_data **src_stack, t_data **dst_stack)
{
	t_data	*head;

	if (stack_len(*src_stack) == 0)
		return ;
	head = *src_stack;
	*src_stack = head->next;
	head->next = *dst_stack;
	*dst_stack = head;
}

void	push_a(t_data **stack_b, t_data **stack_a)
{
	push(stack_b, stack_a);
	ft_printf("pa\n");
}

void	push_b(t_data **stack_a, t_data **stack_b)
{
	push(stack_a, stack_b);
	ft_printf("pb\n");
}
