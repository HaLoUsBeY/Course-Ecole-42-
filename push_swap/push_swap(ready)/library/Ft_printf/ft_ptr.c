/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:14:07 by haloztur          #+#    #+#             */
/*   Updated: 2024/12/10 15:14:07 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr(void *ptr)
{
	unsigned long long	address;
	int					count;

	if (!ptr)
		return (ft_putstr("(nil)"));
	count = 0;
	address = (unsigned long long)ptr;
	count += ft_putstr("0x");
	count += ft_puthexa(address, 0);
	return (count);
}
