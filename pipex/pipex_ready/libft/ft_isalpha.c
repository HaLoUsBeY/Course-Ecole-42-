/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:26:31 by haloztur          #+#    #+#             */
/*   Updated: 2024/10/12 14:26:31 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int str)
{
	if (('a' <= str && 'z' >= str)
		|| ('A' <= str && 'Z' >= str))
		return (1);
	return (0);
}
