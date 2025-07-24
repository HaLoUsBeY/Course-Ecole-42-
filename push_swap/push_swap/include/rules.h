#ifndef RULES_H
# define RULES_H

# include "sort.h"

void	push_a(p_data **stack_b, p_data **stack_a);
void	push_b(p_data **stack_a, p_data **stack_b);

void	reverse_rotate_a(p_data **stack_a);
void	reverse_rotate_b(p_data **stack_b);

void	rotate_a(p_data **stack_a);
void	rotate_b(p_data **stack_b);

void	swap_a(p_data **stack_a);
void	swap_b(p_data **stack_b);

#endif