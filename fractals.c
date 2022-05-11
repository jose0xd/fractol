/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:20:40 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/11 16:13:49 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(t_complex c, int max_iter, void *args)
{
	t_complex	z;
	t_complex	z2;
	int			i;

	(void)args;
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

int	julia(t_complex z, int max_iter, void *args)
{
	t_complex	z2;
	int			i;
	t_complex	c;

	z2.x = z.x * z.x;
	z2.y = z.y * z.y;
	c = *(t_complex *)args;
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

int	burningship(t_complex c, int max_iter, void *args)
{
	t_complex	z;
	t_complex	z2;
	int			i;
	double		prod;

	(void)args;
	z.x = 0;
	z.y = 0;
	z2.x = 0;
	z2.y = 0;
	i = 0;
	while (i < max_iter && z2.x + z2.y < 4)
	{
		prod = z.x * z.y;
		if (prod < 0)
			prod = -prod;
		z.y = 2 * prod + c.y;
		z.x = z2.x - z2.y + c.x;
		z2.x = z.x * z.x;
		z2.y = z.y * z.y;
		i++;
	}
	if (i == max_iter)
		return (0);
	return (i);
}
