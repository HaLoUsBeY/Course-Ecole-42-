/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runnersort_3_4_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:11:08 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/26 14:57:28 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	runner_sort_3(p_data **a_stack)
{
	int	first;
	int	second;
	int	third;

	first = (*a_stack)->data;
	second = (*a_stack)->next->data;
	third = (*a_stack)->next->next->data;
	if (first > second && second > third && first > third)
	{
		sortexe(a_stack, NULL, SWAP_A);
		sortexe(a_stack, NULL, REVERSE_ROTATE_A);
	}
	else if (first < second && second > third && first < third)
	{
		sortexe(a_stack, NULL, SWAP_A);
		sortexe(a_stack, NULL, ROTATE_A);
	}
	else if (first > second && second < third && first > third)
		sortexe(a_stack, NULL, ROTATE_A);
	else if (first < second && second > third && first > third)
		sortexe(a_stack, NULL, REVERSE_ROTATE_A);
	else if (first > second && second < third && first < third)
		sortexe(a_stack, NULL, SWAP_A);
}

void	runner_sort_4_or_5(p_data **a_a_stack, p_data **b_a_stack, int size)
{
	int	min_pos;
	int	i;

	i = -1;
	while (++i < size - 3)
	{
		min_pos = ft_min_value(a_a_stack);
		lurk_middle(a_a_stack, min_pos);
		sortexe(a_a_stack, b_a_stack, PUSH_B);
	}
	runner_sort_3(a_a_stack);
	while (*b_a_stack)
		sortexe(a_a_stack, b_a_stack, PUSH_A);
}