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

static void drawline(int x0, int y0, int x1, int y1)
{
	void *mlx_ptr = mlx_init();
	void *win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Some shit");
	int dx, dy, f, x, y;

	dx = x1-x0;
	dy = y1-y0;
	x = x0;
	y = y0;
	f = 2*dy-dx;

	while (x < x1)
	{
		if (f >= 0)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000ff);
			y=y+1;
			f=f+2*dy-2*dx;
		}
		else
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000ff);
			f = f+2*dy;
		}
		x = x+1;
	}
}

int	main(void)
{
	int x0, y0, x1, y1, dx, dy;
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Some shit");
	//mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0x0000ff);
	//mlx_key_hook (win_ptr, key_press, (void *)0);
	printf("Enter co-ordinates of first point and second: ");
	scanf("%d%d%D%D", &x0, &y0, &x1, &y1);
    drawline(x0, y0, x1, y1);
	mlx_loop(mlx_ptr);
}
