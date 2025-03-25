#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../library/Ft_printf/ft_printf.h"
# include "../library/libft/libft.h"
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

int is_spaces(char *str);
void	argv_check(char **av);
char	**totalarg(int argc, char **argv);
int is_space(char c);
void trim_spaces(char *str);
void	ft_free(char **tab);
int is_int(char **av);
int is_duplacte(char **tab);
int ft_is_digit(char **tab);
void    err_finds(void);
p_data	*get_node(int value);
int	is_true_sorted(p_data *astack, s_machine value);
int	stack_len(p_data *stack);
void ft_free_stacks(p_data **astack, p_data **bstack);

#endif