/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:25:40 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/27 14:45:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

char	**totalarg(int argc, char **argv, int i)
{
	char	*result;
	char	**args;
	int		total_len;
	int		pos;
	int		len;

	pos = 0;
	total_len = 0;
	while (++i < argc)
		total_len += ft_strlen(argv[i]) + 1;
	result = (char *)malloc(total_len * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (++i < argc)
	{
		len = ft_strlen(argv[i]);
		ft_memcpy(result + pos, argv[i], len);
		pos += len;
		if (i < argc - 1)
			result[pos++] = ' ';
	}
	result[pos] = '\0';
	return (args = ft_split(result, ' '), free(result), args);
}

t_data	*get_node(int value)
{
	t_data	*nodes;

	nodes = (t_data *)malloc(sizeof(t_data));
	if (!nodes)
		return (NULL);
	nodes->data = value;
	nodes->next = NULL;
	return (nodes);
}

int	is_true_sorted(t_data *astack, t_machine value)
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

int	stack_len(t_data *stack)
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
