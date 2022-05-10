/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:41:11 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/10 23:21:32 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#define HEIGHT 800
#define WIDTH 800

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_pixel
{
	int	x;
	int	y;
}	t_pixel;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	int			height;
	int			width;
	int			max_iter;
	double		range;
	t_complex	midpoint;
}	t_vars;

t_complex	pixel_to_complex(t_vars *vars, t_pixel p)
{
	t_complex	c;

	c.x = vars->midpoint.x
		+ 2 * vars->range * (p.x / (double)vars->width - 0.5);
	c.y = vars->midpoint.y
		+ 2 * vars->range * (p.y / (double)vars->height - 0.5);
	return (c);
}

int	mandelbrot(t_complex c, int max_iter)
{
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;
	int		i;

	zx = 0;
	zy = 0;
	zx2 = 0;
	zy2 = 0;
	i = 0;
	while (i < max_iter && zx2 + zy2 < 4)
	{
		zy = 2 * zx * zy + c.y;
		zx = zx2 - zy2 + c.x;
		zx2 = zx * zx;
		zy2 = zy * zy;
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
			iter = mandelbrot(c, vars->max_iter);
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

int	mouse(int button, int x, int y, void *param)
{
	t_vars	*vars;
	t_pixel	p;

	vars = (t_vars *)param;
	p.x = x;
	p.y = y;
	if (button == 4)
	{
		vars->midpoint = pixel_to_complex(vars, p);
		vars->range *= 0.5;
	}
	else if (button == 5)
	{
		vars->midpoint = pixel_to_complex(vars, p);
		vars->range *= 1.5;
	}
	plot_mandel(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.width = WIDTH;
	vars.height = HEIGHT;
	vars.max_iter = 100;
	vars.range = 2.5;
	vars.midpoint.x = 0;
	vars.midpoint.y = 0;
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, vars.width, vars.height, "Fractol");
	vars.img.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	plot_mandel(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	mlx_mouse_hook(vars.mlx_win, mouse, &vars);
	mlx_loop(vars.mlx);
}
