/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:38:18 by haloztur          #+#    #+#             */
/*   Updated: 2024/12/10 14:38:18 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa(unsigned long long number, int uppercase)
{
	int		count;
	char	*hex_digit;

	if (uppercase)
		hex_digit = "0123456789ABCDEF";
	else
		hex_digit = "0123456789abcdef";
	count = 0;
	if (number >= 16)
		count += ft_puthexa(number / 16, uppercase);
	count += ft_putchar(hex_digit[number % 16]);
	return (count);
}
