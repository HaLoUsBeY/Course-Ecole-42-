/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:36:43 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/27 14:46:28 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "library/Ft_printf/ft_printf.h"
# include "library/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct push_data
{
	int					data;
	struct push_data	*next;
}	t_data;

typedef enum state_machine
{
	INCREASING ,
	DECREASING
}	t_machine;

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
}	t_sorting;

void	start_stacks(t_data ***astack, t_data ***bstack);
t_data	**getfullstack(t_data **astack, char **argv);

int		ft_is_duplicate(char **tab);
int		ft_is_int(char **av);
int		ft_is_digit(char **tab);

char	**totalarg(int argc, char **argv, int i);
t_data	*get_node(int value);
int		is_true_sorted(t_data *astack, t_machine value);
int		stack_len(t_data *stack);

void	err_finds(void);
void	argv_check(char **av);

void	ft_free(char **tab);
void	ft_free_stacks(t_data **a_stack, t_data **b_stack);

int		is_space(char c);
void	trim_spaces(char *str);
int		is_spaces(char *str);

int		ft_min_value(t_data **a_stack);
void	lurk_middle(t_data **a_stack, int min_tab);

void	runner_sort_3(t_data **a_stack);
void	runner_sort_4_or_5(t_data **a_a_stack, t_data **b_a_stack, int size);

void	quick_sort_b(t_data **stack_a, t_data **stack_b, int len, int i);
void	quick_sort_a(t_data **stack_a, t_data **stack_b, int len);

void	sortexe(t_data **astack, t_data **bstack, t_sorting action_type);
int		sort_stack(t_data **astack, t_data **bstack);

void	push_a(t_data **stack_b, t_data **stack_a);
void	push_b(t_data **stack_a, t_data **stack_b);

void	reverse_rotate_a(t_data **stack_a);
void	reverse_rotate_b(t_data **stack_b);

void	rotate_a(t_data **stack_a);
void	rotate_b(t_data **stack_b);

void	swap_a(t_data **stack_a);
void	swap_b(t_data **stack_b);

#endif