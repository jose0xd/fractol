/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:41:11 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/11 16:30:29 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "fractol.h"

t_complex	pixel_to_complex(t_vars *vars, t_pixel p)
{
	t_complex	c;

	c.x = vars->midpoint.x
		+ 2 * vars->range * (p.x / (double)vars->width - 0.5);
	c.y = vars->midpoint.y
		+ 2 * vars->range * (p.y / (double)vars->height - 0.5);
	return (c);
}

void	plot_fractal(t_vars *vars)
{
	char		*dst;
	int			color;
	t_pixel		p;
	t_complex	c;
	int			iter;

	p.y = -1;
	while (++p.y < vars->height)
	{
		p.x = -1;
		while (++p.x < vars->width)
		{
			c = pixel_to_complex(vars, p);
			iter = vars->fractal(c, vars->max_iter, &vars->c_julia);
			if (iter)
				color = 0x80ff80 + iter * 10;
			else
				color = 0;
			dst = vars->img.addr + (p.y * vars->img.line_length
					+ p.x * (vars->img.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

void	parse_args(int ac, char **av, t_vars *vars)
{
	if (ac == 1)
	{
		puts("Usage: fractol fractal-num\n\t1, 2 or 3");
		exit(0);
	}
	if (av[1][0] == '1')
	{
		vars->midpoint = (t_complex){-1, 0};
		vars->fractal = mandelbrot;
	}
	else if (av[1][0] == '2')
	{
		vars->midpoint = (t_complex){0, 0};
		vars->fractal = julia;
		vars->c_julia = (t_complex){-0.4, 0.6};
		if (ac >= 4)
			vars->c_julia = (t_complex){atof(av[2]), atof(av[3])};
	}
	else if (av[1][0] == '3')
	{
		vars->midpoint = (t_complex){-1, 0};
		vars->fractal = burningship;
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;

	parse_args(ac, av, &vars);
	vars.width = WIDTH;
	vars.height = HEIGHT;
	vars.max_iter = 100;
	vars.range = 2.5;
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, vars.width, vars.height, "Fractol");
	vars.img.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	plot_fractal(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_mouse_hook(vars.mlx_win, mouse, &vars);
	mlx_key_hook(vars.mlx_win, keys, &vars);
	mlx_hook(vars.mlx_win, 17, 0, destroy, &vars);
	mlx_loop(vars.mlx);
}
