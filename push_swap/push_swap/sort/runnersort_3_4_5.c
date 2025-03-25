/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runnersort_3_4_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:11:08 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/25 22:11:08 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sort.h"

void	runner_sort_3(p_data **stack)
{
	int	first;
	int	second;
	int	third;

	first = (*stack)->data;
	second = (*stack)->next->data;
	third = (*stack)->next->next->data;
	if (first > second && second > third && first > third)
	{
		sortexe(stack, NULL, SWAP_A);
		sortexe(stack, NULL, REVERSE_ROTATE_A);
	}
	else if (first < second && second > third && first < third)
	{
		sortexe(stack, NULL, SWAP_A);
		sortexe(stack, NULL, ROTATE_A);
	}
	else if (first > second && second < third && first > third)
		sortexe(stack, NULL, ROTATE_A);
	else if (first < second && second > third && first > third)
		sortexe(stack, NULL, REVERSE_ROTATE_A);
	else if (first > second && second < third && first < third)
		sortexe(stack, NULL, SWAP_A);
}

void	runner_sort_4_or_5(p_data **stack_a, p_data **stack_b, int size)
{
	int	min_pos;
	int	i;

	i = -1;
	while (++i < size - 3)
	{
		min_pos = ft_min_value(stack_a);
		lurk_middle(stack_a, min_pos);
		sortexe(stack_a, stack_b, PUSH_B);
	}
	runner_sort_3(stack_a);
	while (*stack_b)
		sortexe(stack_a, stack_b, PUSH_A);
}