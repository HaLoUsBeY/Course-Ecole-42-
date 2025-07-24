#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "library/Ft_printf/ft_printf.h"
# include "library/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>


typedef struct push_data
{
	int		data;
	struct push_data	*next;
}	p_data;

typedef enum state_machine
{
	INCREASING ,
	DECREASING 
}	s_machine;

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

void start_stacks(p_data ***astack, p_data ***bstack);
p_data **getfullstack(p_data **astack, char **argv);

int ft_is_duplicate(char **tab);
int ft_is_int(char **av);
int ft_is_digit(char **tab);


char	**totalarg(int argc, char **argv, int i);
p_data	*get_node(int value);
int	is_true_sorted(p_data *astack, s_machine value);
int	stack_len(p_data *stack);


void    err_finds(void);
void    argv_check(char **av);

void	ft_free(char **tab);
void ft_free_stacks(p_data **a_stack, p_data **b_stack);

int is_space(char c);
void trim_spaces(char *str);
int is_spaces(char *str);

int	ft_min_value(p_data **a_stack);
void	lurk_middle(p_data **a_stack, int min_tab);

void	runner_sort_3(p_data **a_stack);
void	runner_sort_4_or_5(p_data **a_a_stack, p_data **b_a_stack, int size);

void	quick_sort_b(p_data **stack_a, p_data **stack_b, int len, int i);
void	quick_sort_a(p_data **stack_a, p_data **stack_b, int len);

void	sortexe(p_data **astack, p_data **bstack, sorting action_type);
int	sort_stack(p_data **astack, p_data **bstack);

void	push_a(p_data **stack_b, p_data **stack_a);
void	push_b(p_data **stack_a, p_data **stack_b);

void	reverse_rotate_a(p_data **stack_a);
void	reverse_rotate_b(p_data **stack_b);

void	rotate_a(p_data **stack_a);
void	rotate_b(p_data **stack_b);

void	swap_a(p_data **stack_a);
void	swap_b(p_data **stack_b);

#endif