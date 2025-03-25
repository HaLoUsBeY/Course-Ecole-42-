/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushstack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:24:05 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/25 23:24:05 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rules.h"

static void	push(p_data **src_stack, p_data **dst_stack)
{
	p_data	*head;

	if (stack_len(*src_stack) == 0)
		return ;
	head = *src_stack;
	*src_stack = head->next;
	head->next = *dst_stack;
	*dst_stack = head;
}

void	push_a(p_data **stack_b, p_data **stack_a)
{
	push(stack_b, stack_a);
	ft_printf("pa\n");
}

void	push_b(p_data **stack_a, p_data **stack_b)
{
	push(stack_a, stack_b);
	ft_printf("pb\n");
}