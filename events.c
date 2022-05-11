/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:49:15 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/11 11:50:19 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "fractol.h"

int	mouse(int button, int x, int y, void *param)
{
	t_vars	*vars;
	t_pixel	p;

	vars = (t_vars *)param;
	p = (t_pixel){x, y};
	if (button == 4)
	{
		vars->midpoint = pixel_to_complex(vars, p);
		vars->range *= 0.5;
		vars->max_iter *= 1.05;
	}
	else if (button == 5)
	{
		vars->midpoint = pixel_to_complex(vars, p);
		vars->range *= 1.5;
		vars->max_iter *= 0.95;
		if (vars->max_iter < 100)
			vars->max_iter = 100;
	}
	plot_mandel(vars);
	printf("range: %.16lf, max_iter: %d, midpoint: %.16lf, %.16lf\n",
		vars->range, vars->max_iter, vars->midpoint.x, vars->midpoint.y);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
	return (0);
}

static void	extra_keys(int key, t_vars *vars)
{
	if (key == SPACE)
		vars->max_iter += 10;
	else if (key == BACKSPACE)
		vars->max_iter -= 10;
	else if (key == ENTER)
	{
		vars->max_iter = 100;
		vars->range = 2.5;
		vars->midpoint.x = -1;
		vars->midpoint.y = 0;
	}
}

int	keys(int key, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (key == UP)
		vars->midpoint.y -= vars->range / 2;
	else if (key == DOWN)
		vars->midpoint.y += vars->range / 2;
	else if (key == LEFT)
		vars->midpoint.x -= vars->range / 2;
	else if (key == RIGHT)
		vars->midpoint.x += vars->range / 2;
	else if (key == ESC)
		exit(0);
	else
		extra_keys(key, vars);
	plot_mandel(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
	return (0);
}
