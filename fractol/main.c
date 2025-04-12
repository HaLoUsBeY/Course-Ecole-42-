/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:01:08 by haloztur          #+#    #+#             */
/*   Updated: 2025/04/12 16:01:08 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	int	checker(int ac, char **av)
{
	if (ac != 2 && ac != 4)
		return (0);
	if (ac == 2)
	{
		if (ft_strncmp(av[1], "mandelbrot", ft_strlen("mandelbrot")) != 0)
			return (0);
	}
	else if (ac == 4)
	{
		if (ft_strncmp(av[1], "julia", ft_strlen("julia")) != 0)
			return (0);
		if (!ft_double(av[2]) || !ft_double(av[3]))
		{
			ft_putstr_fd("there should be only decimal numbers\n", 1);
			return (0);
		}
		if (ft_datoi(av[2]) > __DBL_MAX__ || ft_datoi(av[2]) < -__DBL_MAX__
			|| ft_datoi(av[3]) > __DBL_MAX__ || ft_datoi(av[3]) < -__DBL_MAX__)
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_fractal	*fractal;

	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
		return (0);
	if (!checker(ac, av))
	{
		ft_putendl_fd("Usage: ./fractol <mandelbrot> |", 1);
		ft_putendl_fd("| ./fractol <julia> 'v1' 'v2'", 1);
		free(fractal);
		exit(127);
	}
	fractal_init(fractal, av[1]);
	if (ac == 4)
	{
		fractal->julia_x = ft_datoi(av[2]);
		fractal->julia_y = ft_datoi(av[3]);
	}
	runner(fractal);
	controllers(fractal);
	mlx_loop(fractal->mlx);
	free(fractal);
	return (0);
}
