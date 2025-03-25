/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:06:01 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/25 17:06:01 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

char	**totalarg(int argc, char **argv)
{
	char	*result;
	char	**args;
	int		i;
	int		total_len;
	int		pos;

	total_len = 0;
	i = 1;
	pos = 0;
	while (i < argc)
	{
		total_len += ft_strlen(argv[i]) + 1;
		i++;
	}
	result = (char *)malloc(total_len * sizeof(char));
	if (!result)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		int len = ft_strlen(argv[i]);
		ft_memcpy(result + pos, argv[i], len);
		pos += len;
		if (i < argc - 1)
			result[pos++] = ' ';
		i++;
	}
	result[pos] = '\0';
	args = ft_split(result, ' ');
	free(result);
	return (args);
}

p_data	*get_node(int value)
{
	p_data	*nodes;

	nodes = (p_data *)malloc(sizeof(p_data));
	if (!nodes)
		return (NULL);
	nodes->data = value;
	nodes->next = NULL;
	return (nodes);
}

int	is_true_sorted(p_data *astack, s_machine value)
{
	while (astack->next)
	{
		if ((value == INCREASING && (astack->data > astack->next->data))
			|| (value == DECREASING && (astack->data < astack->next->data)))
			return (0);
		astack = astack->next;
	}
	return (1);
}

int	stack_len(p_data *stack)
{
	int	result;

	result = 0;
	while (stack != NULL)
	{
		result++;
		stack = stack->next;
	}
	return (result);
}