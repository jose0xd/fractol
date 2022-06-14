/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:41:11 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/14 18:18:58 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

int	get_color(int iter, int palette)
{
	int			r;
	int			g;
	int			b;
	static int	map[][3] = {{66, 30, 15}, {25, 7, 26}, {9, 1, 47}, {4, 4, 73},
	{0, 7, 100}, {12, 44, 138}, {24, 82, 177}, {57, 125, 209},
	{134, 181, 229}, {211, 236, 248}, {241, 233, 191}, {248, 201, 95},
	{255, 170, 0}, {204, 128, 0}, {153, 87, 0}, {106, 52, 3}};

	if (palette == 1)
	{
		r = sin(5 * iter + 0) * 127 + 128;
		g = sin(5 * iter + 2) * 127 + 128;
		b = sin(5 * iter + 4) * 127 + 128;
	}
	else if (palette == 2)
	{
		r = map[iter % 16][0];
		g = map[iter % 16][1];
		b = map[iter % 16][2];
	}
	else
		return (0x80ff80 + iter * 10);
	return (r << 16 | g << 8 | b);
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
				color = get_color(iter, vars->palette);
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
	if (ac == 1 || (av[1][0] != '1' && av[1][0] != '2' && av[1][0] != '3'))
	{
		printf("Usage: fractol <fractal-num> [c.x c.y]\n");
		printf("\t1: Mandelbrot, 2: Julia [complex number] "\
			"or 3: Burningship\n");
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
			vars->c_julia = (t_complex){ft_atof(av[2]), ft_atof(av[3])};
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
	vars.palette = 0;
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
