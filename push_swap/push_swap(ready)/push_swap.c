/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:43 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/27 14:44:15 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	start_stacks(t_data ***astack, t_data ***bstack)
{
	*astack = (t_data **)malloc(sizeof(t_data *));
	*bstack = (t_data **)malloc(sizeof(t_data *));
	if (!(*astack) || !(*bstack))
		exit(1);
	**astack = NULL;
	**bstack = NULL;
}

t_data	**getfullstack(t_data **astack, char **argv)
{
	int		i;
	int		result;
	t_data	*node;
	t_data	*current_node;

	i = 0;
	while (argv[i])
	{
		result = ft_atoi(argv[i]);
		node = get_node(result);
		if (*astack == NULL)
			*astack = node;
		else
		{
			current_node = *astack;
			while (current_node->next)
				current_node = current_node->next;
			current_node->next = node;
		}
		i++;
	}
	return (astack);
}

static	void	controlp_arg(char **as)
{
	if (ft_is_int(as) == -1 || ft_is_duplicate(as) == -1
		|| ft_is_digit(as) == -1)
		err_finds();
}

int	main(int ac, char **av)
{
	char	**as;
	t_data	**adata;
	t_data	**bdata;

	if (ac < 2)
		return (0);
	if (!av)
		return (1);
	argv_check(av);
	as = totalarg(ac, av, 0);
	controlp_arg(as);
	start_stacks(&adata, &bdata);
	adata = getfullstack(adata, as);
	if (!is_true_sorted(*adata, INCREASING))
		sort_stack(adata, bdata);
	ft_free_stacks(adata, bdata);
	ft_free(as);
	return (0);
}
