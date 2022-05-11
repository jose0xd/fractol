/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:48:27 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/11 11:48:28 by jarredon         ###   ########.fr       */
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

int			mouse(int button, int x, int y, void *param);
int			keys(int key, void *param);

t_complex	pixel_to_complex(t_vars *vars, t_pixel p);
void		plot_mandel(t_vars *vars);

#endif
