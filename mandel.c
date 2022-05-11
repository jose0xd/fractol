/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:41:11 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/11 12:20:26 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
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

static int	mandelbrot(t_complex c, int max_iter)
{
	t_complex	z;
	t_complex	z2;
	int			i;

	z.x = 0;
	z.y = 0;
	z2.x = 0;
	z2.y = 0;
	i = 0;
	while (i < max_iter && z2.x + z2.y < 4)
	{
		z.y = 2 * z.x * z.y + c.y;
		z.x = z2.x - z2.y + c.x;
		z2.x = z.x * z.x;
		z2.y = z.y * z.y;
		i++;
	}
	if (i == max_iter)
		return (0);
	return (i);
}

/*t_complex g_c = { 0.285, 0.01 };*/
t_complex g_c = { -0.4, 0.6 };
/*t_complex g_c = { -0.835, -0.2321 };*/
/*t_complex g_c = { −0.7269 + 0.1889 };*/

static int	julia(t_complex z, t_complex c, int max_iter)
{
	t_complex	z2;
	int			i;

	z2.x = z.x * z.x;
	z2.y = z.y * z.y;
	i = 0;
	while (i < max_iter && z2.x + z2.y < 4)
	{
		z.y = 2 * z.x * z.y + c.y;
		z.x = z2.x - z2.y + c.x;
		z2.x = z.x * z.x;
		z2.y = z.y * z.y;
		i++;
	}
	if (i == max_iter)
		return (0);
	return (i);
}

double	absolut(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	burningship(t_complex c, int max_iter)
{
	t_complex	z;
	t_complex	z2;
	int			i;

	z.x = 0;
	z.y = 0;
	z2.x = 0;
	z2.y = 0;
	i = 0;
	while (i < max_iter && z2.x + z2.y < 4)
	{
		z.y = 2 * absolut(z.x * z.y) + c.y;
		z.x = z2.x - z2.y + c.x;
		z2.x = z.x * z.x;
		z2.y = z.y * z.y;
		i++;
	}
	if (i == max_iter)
		return (0);
	return (i);
}

void	plot_mandel(t_vars *vars)
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
			/*iter = mandelbrot(c, vars->max_iter);*/
			(void)mandelbrot;
			iter = julia(c, g_c, vars->max_iter);
			/*(void)julia;*/
			/*iter = burningship(c, vars->max_iter);*/
			(void)burningship;
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

int	main(void)
{
	t_vars	vars;

	vars.width = WIDTH;
	vars.height = HEIGHT;
	vars.max_iter = 100;
	vars.range = 2.5;
	vars.midpoint.x = -1;
	vars.midpoint.y = 0;
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, vars.width, vars.height, "Fractol");
	vars.img.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	plot_mandel(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_mouse_hook(vars.mlx_win, mouse, &vars);
	mlx_key_hook(vars.mlx_win, keys, &vars);
	mlx_loop(vars.mlx);
}
