/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:43 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/26 16:07:23 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void start_stacks(p_data ***astack, p_data ***bstack)
{
	*astack = (p_data **)malloc(sizeof(p_data *));
	*bstack = (p_data **)malloc(sizeof(p_data *));
	if (!(*astack) || !(*bstack))
		exit(1);
	**astack = NULL;
	**bstack = NULL;
}

p_data **getfullstack(p_data **astack, char **argv)
{
	int		i;
	int		result;
	p_data	*node;
	p_data	*current_node;

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

static void controlp_arg(char **as)
{
	if (ft_is_int(as) == -1 || ft_is_duplicate(as) == -1 || ft_is_digit(as) == -1)
		err_finds();
}

int	main(int ac, char **av)
{
	char	**as;
	p_data	**adata;
	p_data	**bdata;

	if (ac < 2)
		return (0);
	if (!av)
		return (1);
	argv_check(av);
	as = totalarg(ac, av);
	controlp_arg(as);
	start_stacks(&adata, &bdata);
	adata = getfullstack(adata, as);
	if (!is_true_sorted(*adata, INCREASING))
		sort_stack(adata, bdata);
	ft_free_stacks(adata, bdata);
	ft_free(as);
	return (0);
}
