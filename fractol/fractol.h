/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:57:27 by haloztur          #+#    #+#             */
/*   Updated: 2025/04/12 15:57:27 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include "library/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define ESC 65307
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define ITERATION 42
# define SIZE 800

typedef struct s_fractal
{
	char	*name;
	void	*mlx;
	void	*window;
	void	*img;
	void	*image_to_ptr;
	int		x;
	int		y;
	int		bpp;
	int		end;
	int		index_line;
	int		color;
	double	julia_x;
	double	julia_y;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	cx;
	double	cy;
	double	zx;
	double	zy;
}	t_fractal;

void	controllers(t_fractal *fractal);

int		ft_double(char *s);
double	ft_datoi(char *s);

void	fractal_init(t_fractal *fractal, char *name);

void	runner(t_fractal *fractal);

#endif
