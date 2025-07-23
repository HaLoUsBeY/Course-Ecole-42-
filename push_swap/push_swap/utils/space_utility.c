/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:58:53 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/25 14:58:53 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

void trim_spaces(char *str)
{
    int start;
    int end;
	int i;

	start = 0;
	end = 0;
    while (str[start] && is_space(str[start]))
        start++;
    end = start;
    while (str[end])
        end++;
    while (end > start && is_space(str[end - 1]))
        end--;
    if (start != end)
    {
        i = 0;
        while (start < end)
            str[i++] = str[start++];
        str[i] = '\0';
    }
    else
        str[0] = '\0';
}

int is_spaces(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (!is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}