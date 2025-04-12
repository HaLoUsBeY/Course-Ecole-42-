/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:28:57 by haloztur          #+#    #+#             */
/*   Updated: 2025/04/12 10:28:57 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	close_window(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img);
	mlx_destroy_window(fractal->mlx, fractal->window);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	free(fractal);
	exit(0);
}

static int	key_button(int button, t_fractal *fractal)
{
	if (button == ESC)
		close_window(fractal);
	return (0);
}

static void	zoom(t_fractal *fractal, int x, int y, int zoom)
{
	double	zoom_level;

	zoom_level = 1.4;
	if (zoom == 1)
	{
		fractal->shift_x = (x / fractal->zoom + fractal->shift_x) - (x
				/ (fractal->zoom * zoom_level));
		fractal->shift_y = (y / fractal->zoom + fractal->shift_y) - (y
				/ (fractal->zoom * zoom_level));
		fractal->zoom *= zoom_level;
	}
	else if (zoom == -1)
	{
		fractal->shift_x = (x / fractal->zoom + fractal->shift_x) - (x
				/ (fractal->zoom / zoom_level));
		fractal->shift_y = (y / fractal->zoom + fractal->shift_y) - (y
				/ (fractal->zoom / zoom_level));
		fractal->zoom /= zoom_level;
	}
}


static int	mouse_scroll(int button, int x, int y, t_fractal *fractal)
{
	if (button == SCROLL_UP)
		zoom(fractal, x, y, 1);
	else if (button == SCROLL_DOWN)
		zoom(fractal, x, y, -1);
	runner(fractal);
	return (0);
}
void	controllers(t_fractal *fractal)
{
	mlx_key_hook(fractal->window, key_button, fractal);
	mlx_mouse_hook(fractal->window, mouse_scroll, fractal);
	mlx_hook(fractal->window, 17, 0L, close_window, fractal);
}
