/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:54:44 by haloztur          #+#    #+#             */
/*   Updated: 2024/12/20 20:02:03 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_types(va_list arg, char types)
{
	int	count;

	count = 0;
	if (types == 'c')
		count += ft_putchar(va_arg(arg, int));
	else if (types == 's')
		count += ft_putstr(va_arg(arg, char *));
	else if (types == 'i' || types == 'd')
		count += ft_putnbr(va_arg(arg, int));
	else if (types == 'p')
		count += ft_ptr(va_arg(arg, void *));
	else if (types == 'u')
		count += ft_putunsigint(va_arg(arg, unsigned int));
	else if (types == 'x')
		count += ft_puthexa(va_arg(arg, unsigned int), 0);
	else if (types == 'X')
		count += ft_puthexa(va_arg(arg, unsigned int), 1);
	else if (types == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		value;
	int		i;

	value = 0;
	i = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			value += ft_types(arg, str[i]);
		}
		else
			value += ft_putchar(str[i]);
		i++;
	}
	va_end(arg);
	return (value);
}
