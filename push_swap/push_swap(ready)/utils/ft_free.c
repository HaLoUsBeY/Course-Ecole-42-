/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:59:27 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/27 14:44:15 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_stacks(t_data **a_stack, t_data **b_stack)
{
	t_data	*node;

	while (*a_stack)
	{
		node = *a_stack;
		*a_stack = (*a_stack)->next;
		free(node);
	}
	while (*b_stack)
	{
		node = *b_stack;
		*b_stack = (*b_stack)->next;
		free(node);
	}
	free(a_stack);
	free(b_stack);
}
