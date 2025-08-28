/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:37:59 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 10:53:14 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int    is_valid_space(char c, char next, int *flag)
{
    if (ft_isspace(c) && next)
    {
        if (++(*flag) == 1)
            return (1);
        return (0);
    }
    return (-1);
}

int    ft_check(int ac, char **av)
{
    int    i;
    int    j;
    int    flag;
    int    res;

    i = 1;
    while (i < ac)
    {
        j = 0;
        flag = 0;
        if (ft_isspace(av[i][0]))
            return (1);
        while (av[i][j])
        {
            if (ft_isdigit(av[i][j]))
                j++;
            else if ((res = is_valid_space(av[i][j], av[i][j + 1], &flag)) == 1)
                j++;
            else
                return (1);
        }
        i++;
    }
    return (0);
}

unsigned int    check_and_ret(char *str)
{
    unsigned int num;

    if (ft_check(2, (char *[]){NULL, str}))
        error_exit("incorrect usage");
    num = ft_atoi_u(str);
    if (num == 0)
        error_exit("incorrect usage");
    return (num);
}
