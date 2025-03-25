/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:59:27 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/25 18:59:27 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_free(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void ft_free_stacks(p_data **astack, p_data **bstack)
{
	p_data *node;

	while (*astack)
	{
		node = *astack;
		*astack = (*astack)->next;
		free(node);
	}
	while (*bstack)
	{
		node = *bstack;
		*bstack = (*bstack)->next;
		free(node);
	}
	free(astack);
	free(bstack);
}