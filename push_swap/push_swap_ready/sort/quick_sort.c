/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:38:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/26 14:58:37 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	temp_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	median(p_data **stack, int len)
{
	p_data	*tmp;
	int		i;
	int		*arr;
	int		median;

	i = -1;
	tmp = *stack;
	arr = (int *)malloc(len * sizeof(int));
	while (++i < len)
	{
		arr[i] = tmp->data;
		tmp = tmp->next;
	}
	temp_sort(arr, len);
	median = arr[len / 2];
	return (free(arr), median);
}

void	quick_sort_b(p_data **stack_a, p_data **stack_b, int len, int i)
{
	int	pivot;
	int	pushed;
	int	rotated;

	if (len <= 1 || is_true_sorted(*stack_b, DECREASING))
	{
		while (len--)
			sortexe(stack_a, stack_b, PUSH_A);
		return ;
	}
	pushed = 0;
	rotated = 0;
	pivot = median(stack_b, len);
	while (i++ < len)
	{
		if ((*stack_b)->data >= pivot && ++pushed)
			sortexe(stack_a, stack_b, PUSH_A);
		else if (++rotated)
			sortexe(NULL, stack_b, ROTATE_B);
	}
	while (stack_len(*stack_b) > len && rotated--)
		sortexe(NULL, stack_b, REVERSE_ROTATE_B);
	quick_sort_a(stack_a, stack_b, pushed);
	quick_sort_b(stack_a, stack_b, len - pushed, 0);
}

void	quick_sort_a(p_data **stack_a, p_data **stack_b, int len)
{
	int	pivot;
	int	pushed;
	int	rotated;
	int	i;

	if (len <= 1 || is_true_sorted(*stack_a, INCREASING))
		return ;
	i = 0;
	pushed = 0;
	rotated = 0;
	pivot = median(stack_a, len);
	while (i++ < len)
	{
		if ((*stack_a)->data < pivot && ++pushed)
			sortexe(stack_a, stack_b, PUSH_B);
		else if (++rotated)
			sortexe(stack_a, NULL, ROTATE_A);
	}
	while (stack_len(*stack_a) > len && rotated--)
		sortexe(stack_a, NULL, REVERSE_ROTATE_A);
	quick_sort_a(stack_a, stack_b, len - pushed);
	quick_sort_b(stack_a, stack_b, pushed, 0);
}
