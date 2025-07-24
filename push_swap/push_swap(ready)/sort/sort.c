/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:00:17 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/27 14:46:10 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sortexe(t_data **astack, t_data **bstack, t_sorting action_type)
{
	if (action_type == SWAP_A)
		swap_a(astack);
	else if (action_type == SWAP_B)
		swap_b(bstack);
	else if (action_type == PUSH_A)
		push_a(bstack, astack);
	else if (action_type == PUSH_B)
		push_b(astack, bstack);
	else if (action_type == ROTATE_A)
		rotate_a(astack);
	else if (action_type == ROTATE_B)
		rotate_b(bstack);
	else if (action_type == REVERSE_ROTATE_A)
		reverse_rotate_a(astack);
	else if (action_type == REVERSE_ROTATE_B)
		reverse_rotate_b(bstack);
}

int	sort_stack(t_data **astack, t_data **bstack)
{
	int		size;

	size = stack_len(*astack);
	if (size == 2)
		sortexe(astack, NULL, SWAP_A);
	else if (size == 3)
		runner_sort_3(astack);
	else if (size == 4 || size == 5)
		runner_sort_4_or_5(astack, bstack, size);
	else
		quick_sort_a(astack, bstack, size);
	return (0);
}
