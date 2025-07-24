/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:47:37 by haloztur          #+#    #+#             */
/*   Updated: 2024/12/10 10:47:37 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putchar(int c);
int	ft_puthexa(unsigned long long number, int uppercase);
int	ft_putnbr(int nbr);
int	ft_putstr(char *str);
int	ft_putunsigint(unsigned int nbr);
int	ft_types(va_list arg, char types);
int	ft_ptr(void *ptr);

#endif