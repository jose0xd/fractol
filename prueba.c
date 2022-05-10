#include <mlx.h>
#include <math.h>
#include <stdio.h>

/*
int main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}
*/

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
} t_vars;

int max_iter = 200;
int	colors[4] = {0xff0000, 0x00ff00, 0x0000ff, 0x800080};

int	mandelbrot(double cx, double cy)
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
		zy = 2 * zx * zy + cy;
		zx = zx2 - zy2 + cx;
		zx2 = zx * zx;
		zy2 = zy * zy;
		i++;
	}
	if (i == max_iter)
		return (0);
	return (i);
}

double cy_min = -2.0;
double cy_max = 2.0;
double cx_min = -2.5;
double cx_max = 1.5;

void	mandel(t_data *data, int width, int high)
{
	char	*dst;
	int		x;
	int		y;
	int		color;
	double cx, cy;

	y = -1;
	while (++y < high)
	{
		cy = cy_min + y * (cy_max - cy_min) / high;
		x = -1;
		while (++x < width)
		{
			cx = cx_min + x * (cx_max - cx_min) / width;
			int	iter = mandelbrot(cx, cy);
			if (iter)
			{
				/*color = colors[iter % 4];*/
				color = 0x80ff80 + iter * 10;
				dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
				*(unsigned int*)dst = color;
			}
		}
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_rainbow(t_data *data, int width, int high)
{
	char	*dst;
	int		x;
	int		y;
	int		color;
	int		R, G, B;

	color = 0;
	y = -1;
	while (++y < high)
	{
		// sin(frequency*increment)*amplitude + center
		// Desincronizo los incrementos para más colorido
		R = sin(0.03 * y + 0) * 127 + 128;
		G = sin(0.03 * y + 2) * 127 + 128;
		B = sin(0.03 * y + 4) * 127 + 128;
		color = R << 16 | G << 8 | B;
		x = -1;
		while (++x < width)
		{
			dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
			/**(unsigned int*)dst = color;*/
			*(unsigned int*)dst = 0;
		}
	}
}

int	range = 100;

int	f_circle(int x, int y, int width, int high)
{
	float	px;
	float	py;

	px = ((float)x / width) * range - range/2;
	py = ((float)y / high) * range - range/2;
	px = px * width / high;
	if ((px * px) + (py * py) < 200)
		return (1);
	return (0);
}

void	my_circle(t_data *data, int width, int high)
{
	char	*dst;
	int		x;
	int		y;
	int		color;

	y = -1;
	while (++y < high)
	{
		x = -1;
		while (++x < width)
		{
			if (!f_circle(x, y, width, high))
			{
				color = 0x8080FF;
				dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
				*(unsigned int*)dst = color;
			}
		}
	}
}

int	func(int key, void *param)
{
	t_vars	vars = *(t_vars *)param;

	if (key == 125)
		max_iter += 1;
	else if (key == 126)
		max_iter -= 1;
	my_rainbow(&vars.img, 1080, 1080);
	mandel(&vars.img, 1080, 1080);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	/*printf("key: %d\n", key);*/
	return (0);
}

int	mouse(int button, int x, int y, void *param)
{
	t_vars vars = *(t_vars *)param;
	(void)x;
	(void)y;
	if (button == 4)
	{
		cx_min *= 0.5;
		cx_max *= 0.5;
		cy_min *= 0.5;
		cy_max *= 0.5;
	}
	else if (button == 5)
	{
		cx_min *= 1.5;
		cx_max *= 1.5;
		cy_min *= 1.5;
		cy_max *= 1.5;
	}
	my_rainbow(&vars.img, 1080, 1080);
	mandel(&vars.img, 1080, 1080);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1080, 1080, "Hello world!");
	vars.img.img = mlx_new_image(vars.mlx, 1080, 1080);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
								&vars.img.endian);
	/*printf("bits_per_pixel: %d\nline_length: %d\nendian: %d\n",*/
			/*img.bits_per_pixel, img.line_length, img.endian);*/
	/*my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);*/
	/*my_rainbow(&vars.img, 1080, 1080);*/
	/*my_circle(&vars.img, 1080, 1080);*/
	mandel(&vars.img, 1080, 1080);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img.img, 0, 0);
	/*mlx_hook(vars.mlx_win, 2, 1L<<0, func, &vars);*/
	mlx_mouse_hook(vars.mlx_win, mouse, &vars);
	mlx_loop(vars.mlx);
}
