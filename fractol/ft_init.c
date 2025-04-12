/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:48:15 by haloztur          #+#    #+#             */
/*   Updated: 2025/04/12 09:48:15 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fractal_data(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	fractal->color = 0x908f8f;
}

static void	ft_error(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img);
	mlx_destroy_window(fractal->mlx, fractal->window);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	free(fractal);
	ft_putstr_fd("Error\n", 1);
	exit(1);
}

void	fractal_init(t_fractal *fractal, char *name)
{
	fractal_data(fractal);
	fractal->name = name;
	fractal->mlx = mlx_init();
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		fractal->window = mlx_new_window(fractal->mlx, SIZE, SIZE,
				fractal->name);
		fractal->shift_x = -1.4;
		fractal->shift_y = -1.4;
		fractal->zoom = 350;
	}
	else if (!ft_strncmp(fractal->name, "mandel", 6))
	{
		fractal->window = mlx_new_window(fractal->mlx, SIZE, SIZE,
				fractal->name);
		fractal->shift_x = -2;
		fractal->shift_y = -1.30;
		fractal->zoom = 370;
	}
	fractal->img = mlx_new_image(fractal->mlx, SIZE, SIZE);
	if (!fractal->mlx || !fractal->window || !fractal->img)
		ft_error(fractal);
	fractal->image_to_ptr = mlx_get_data_addr(fractal->img, &fractal->bpp,
			&fractal->index_line, &fractal->end);
}
