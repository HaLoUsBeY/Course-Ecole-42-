/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:45:05 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/26 14:54:51 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void    err_finds(void)
{
    ft_putendl_fd("Error", 2);
    exit(1);
}

void    argv_check(char **av)
{
    int i;

    i = 0;
    while (av[i])
    {
        trim_spaces(av[i]);
        if (av[i][0] == '\0' || is_spaces(av[i]))
            err_finds();
        i++;
    }
}