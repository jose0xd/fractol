/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:48:27 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/11 17:42:41 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define HEIGHT 1000
# define WIDTH 1000

# define ENTER 36
# define SPACE 49
# define BACKSPACE 51
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define K1 18
# define K2 19
# define K3 20
# define K4 21
# define K5 23
# define K6 22
# define K7 26
# define K8 28
# define K9 25
# define K0 29

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
	int			(*fractal)(t_complex, int, void *);
	t_complex	c_julia;
	int			palette;
}	t_vars;

// Fractals
int			mandelbrot(t_complex c, int max_iter, void *args);
int			julia(t_complex z, int max_iter, void *args);
int			burningship(t_complex c, int max_iter, void *args);

// Events
int			mouse(int button, int x, int y, void *param);
int			keys(int key, void *param);
int			destroy(void *param);

t_complex	pixel_to_complex(t_vars *vars, t_pixel p);
void		plot_fractal(t_vars *vars);

// Utils
double		ft_atof(char *str);

#endif
