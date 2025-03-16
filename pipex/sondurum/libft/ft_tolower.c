/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:18:11 by haloztur          #+#    #+#             */
/*   Updated: 2024/10/19 19:18:11 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int str)
{
	if (str >= 'A' && str <= 'Z')
		return (str + 32);
	return (str);
}
