#include "./minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int *exit_x(void *param)
{
	param = NULL;
	exit(0);
	return (0);
}

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

int	main(void)
{
	int x0, y0, x1, y1, dx, dy;
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Some Shit");
	//mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xffd700);
//	mlx_string_put(mlx_ptr, win_ptr, 100, 450, 0xffd700, "Fuck you");
	drawline(100, 100, 180, 200, mlx_ptr, win_ptr);
//	mlx_key_hook (win_ptr, key_press, (void *)0);
	mlx_loop(mlx_ptr);
	iso (&100, &100, 100);
	mlx_hook(win_ptr, 17, 1L<<17, exit_x(0), 0);
}
