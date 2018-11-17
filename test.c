#include "./minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int key_press(int key, void *param)
{
	ft_putchar('X');
	return (0);
}

void drawline(int x0, int y0, int x1, int y1, void *mlx_ptr, void *win_ptr)
{
	int dx, dy, f;

	dx = x1 - x0;
	dy = y1 - y0;
	f = dx / 2;

	while (x0 < x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xffd700);
		if (f < 0)
		{
			f = f + dx;
		}
		else
		{
			f = f - dy;
			y0++;
		}
		x0++;
	}
}

int	main(void)
{
	int x0, y0, x1, y1, dx, dy;
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Some shit");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xffd700);
//	mlx_string_put(mlx_ptr, win_ptr, 200, 300, 0xffd700, "Hello");
	drawline(100, 100, 200, 150, mlx_ptr, win_ptr);
	mlx_key_hook (win_ptr, key_press, (void *)0);
	mlx_loop(mlx_ptr);
}
