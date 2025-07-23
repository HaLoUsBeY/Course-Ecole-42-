#ifndef SORT_H
# define SORT_H

# include "push_swap.h"

typedef enum e_sort
{
	PUSH_A,
	PUSH_B,
	SWAP_A,
	SWAP_B,
	ROTATE_A,
	ROTATE_B,
	REVERSE_ROTATE_A,
	REVERSE_ROTATE_B,
}	sorting;

void	sortexe(p_data **astack, p_data **bstack, sorting action_type);
int	sort_stack(p_data **astack, p_data **bstack);
int	ft_min_value(p_data **stack_a);
void	lurk_middle(p_data **stack_a, int min_tab);
void	runner_sort_4_or_5(p_data **stack_a, p_data **stack_b, int size);
void	runner_sort_3(p_data **stack);
void	quick_sort_a(p_data **stack_a, p_data **stack_b, int len);
void	quick_sort_b(p_data **stack_a, p_data **stack_b, int len, int i);

#endif