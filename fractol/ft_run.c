/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:15:34 by haloztur          #+#    #+#             */
/*   Updated: 2025/04/12 10:15:34 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	color_to_pixel(t_fractal *fractal, int color, int x, int y)
{
	int	*buffer;

	buffer = fractal->image_to_ptr;
	buffer[(y * fractal->index_line / 4) + x] = color;
}

static void	mandel(t_fractal *fractal)
{
	int		i;
	double	tmp;

	i = -1;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->shift_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->shift_y;
	while (i < ITERATION)
	{
		tmp = (fractal->zx * fractal->zx) - (fractal->zy * fractal->zy)
			+ fractal->cx;
		fractal->zy = 2.0 * fractal->zy * fractal->zx + fractal->cy;
		fractal->zx = tmp;
		if (fractal->zx * fractal->zx + fractal->zy
			* fractal->zy >= __DBL_MAX__)
			break ;
		i++;
	}
	if (i == ITERATION)
		color_to_pixel(fractal, 0, fractal->x, fractal->y);
	else
		color_to_pixel(fractal, fractal->color * i, fractal->x, fractal->y);
}

static void	julia(t_fractal *fractal)
{
	int		i;
	double	tmp;

	i = 0;
	fractal->cx = fractal->julia_x;
	fractal->cy = fractal->julia_y;
	fractal->zx = (fractal->x / fractal->zoom) + fractal->shift_x;
	fractal->zy = (fractal->y / fractal->zoom) + fractal->shift_y;
	while (i < ITERATION)
	{
		tmp = (fractal->zx * fractal->zx) - (fractal->zy * fractal->zy)
			+ fractal->cx;
		fractal->zy = 2.0 * fractal->zy * fractal->zx + fractal->cy;
		fractal->zx = tmp;
		if (fractal->zx * fractal->zx + fractal->zy
			* fractal->zy >= __DBL_MAX__)
			break ;
		i++;
	}
	if (i == ITERATION)
		color_to_pixel(fractal, 0, fractal->x, fractal->y);
	else
		color_to_pixel(fractal, fractal->color * i, fractal->x, fractal->y);
}

void	runner(t_fractal *fractal)
{
	int	a;
	int	b;

	a = ft_strlen("mandelbrot");
	b = ft_strlen("julia");
	fractal->x = 0;
	fractal->y = 0;
	while (fractal->x < SIZE)
	{
		while (fractal->y < SIZE)
		{
			if (!ft_strncmp(fractal->name, "mandelbrot", a))
				mandel(fractal);
			else if (!ft_strncmp(fractal->name, "julia", b))
				julia(fractal);
			(fractal->y)++;
		}
		fractal->y = 0;
		(fractal->x)++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->img, 0, 0);
}
