/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:52:10 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/27 18:43:31 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "./libft/libft.h"
#include <fcntl.h>

 typedef struct s_point
 {
 	int x;
 	int y;
 }				t_point;

typedef struct			s_map
{
	int				width;
	int				height;
	int				stepx;
	int 			stepy;
	int				total;
	int				x_now;
	int				y_now;
}						t_map;




void draw_x(t_point *point, void *mlx_ptr, void *win_ptr, int i)
{
	int dx;
  	int dy;
  	int x;
  	int y;

	dx = point[i].x - point[i-1].x;
	dy = point[i].y - point[i-1].y;
  	x = point[i - 1].x;
  	while (point[i].x > x)
	{
    	y = point[i - 1].y + dy * (x - point[i - 1].x) / dx;
		// first y + dy * (current x - prev x) / dx;
		mlx_pixel_put(mlx_ptr, win_ptr, 450 + x, 200 + y, 0x5f96c9);
		x++;
	}
}

int key_press(int key, void *param)
{
	if (key == 53)
	{
		exit(1);
	}
	return (0);
}

void draw_line(int x0, int y0, int x1, int y1, int color, void *mlx_ptr, void *win_ptr)
{
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = x1 >= x0 ? 1 : -1;
  int sy = y1 >= y0 ? 1 : -1;

  if (dy <= dx)
  {
    int d = (dy << 1) - dx;
    int d1 = dy << 1;
    int d2 = (dy - dx) << 1;
    mlx_pixel_put(mlx_ptr, win_ptr, 450 + x0, 200 + y0, 0xbaffec);
    for(int x = x0 + sx, y = y0, i = 1; i <= dx; i++, x += sx)
    {
      if ( d >0)
      {
        d += d2;
        y += sy;
      }
      else
        d += d1;
      mlx_pixel_put(mlx_ptr, win_ptr, 450 + x, 200 + y, 0xbaffec);
    }
  }
  else
  {
    int d = (dx << 1) - dy;
    int d1 = dx << 1;
    int d2 = (dx - dy) << 1;
    mlx_pixel_put(mlx_ptr, win_ptr, 450 + x0, 200 + y0, 0xbaffec);
    for(int y = y0 + sy, x = x0, i = 1; i <= dy; i++, y += sy)
    {
      if ( d >0)
      {
        d += d2;
        x += sx;
      }
      else
        d += d1;
      mlx_pixel_put(mlx_ptr, win_ptr, 450 + x, 200 + y, 0xbaffec);
    }
  }
}

void connect_line(t_point *point, t_map *map, void *mlx_ptr, void *win_ptr)
{
	int counter;
	int prev_y;

	counter = 0;

	while(counter < map->total)
	{
		prev_y = counter - map->width;
		if (prev_y >= 0)
		{
			draw_line(point[counter].x, point[counter].y, point[prev_y].x, point[prev_y].y, 0xbaffec, mlx_ptr, win_ptr);
		}
		counter++;
	}
}

void to_coordinates(int massiv, t_point *point, t_map *map, int i, void *mlx_ptr, void *win_ptr )
{
	int dx, dy;
	if (massiv == 0)
	{
		point[i].x = ((map->x_now - map->y_now) + map->stepx) * cos(0.523599);
		point[i].y = (map->y_now + map->x_now) * sin(0.523599);
	}
	else
	{
		point[i].x = ((map->x_now - map->y_now) + map->stepx) * cos(0.523599);;
		point[i].y = -(massiv * 3) + (map->x_now + map->y_now) * sin(0.523599);
	}
	map->x_now = map->x_now + map->stepx;
 //mlx_pixel_put(mlx_ptr, win_ptr, 450 + point[i].x, 200 + point[i].y, 0xab82ff);
	if (i > 0)
	{
		draw_x(point, mlx_ptr, win_ptr, i);
	}
	// printf("This is x %f and y %f and i is : %d\n", point[i].x, point[i].y, i);
}

void map_init(t_map *map, int x, int y)
{
	map->height = y;
	map->width = x;
	map->stepx = 500/x;
	map->stepy = 500/y;
	map->total = x * y;
	map->x_now = 100 - map->stepx;
	map->y_now = 100;
}

void		read_map(char *file, t_map *map, void *mlx_ptr, void *win_ptr)
{
	int fd;
	char *line;
	int x = 0;
	int y = 0;
	int i = 0;
	char **massiv;
	t_point *point;

	fd = open(file, O_RDONLY);
	while(get_next_line(fd, &line) == 1)
	{
		x = ft_count_words(line, ' ');
		y++;
	}
	free(line);
	close(fd);
	map_init(map, x, y);
	point = (t_point*)malloc(sizeof(t_point) * map->total);
	fd = open(file, O_RDONLY);
	while(get_next_line(fd, &line) == 1)
	{
		massiv = ft_strsplit(line, ' ');
		int a = 0;
		while(a < map->width)
		{
			to_coordinates(ft_atoi(massiv[a]), point, map, i, mlx_ptr, win_ptr);
			i++;
			a++;
		}
		a = 0;
		map->x_now = 100 - map->stepx;
		map->y_now = map->y_now + map->stepy;
	}
	connect_line(point, map, mlx_ptr, win_ptr);
}

int main(int argc, char **argv)
{
	void 			*mlx_ptr;
	void 			*win_ptr;
	t_map			*map;

	if (argc == 2)
	{
		map = (t_map*)malloc(sizeof(t_map));
		mlx_ptr = mlx_init();
		win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "My FDF");
		read_map(argv[1], map, mlx_ptr, win_ptr);
		mlx_string_put(mlx_ptr, win_ptr, 400, 100, 0xe6e6fa, "Welcome to FDF");
		mlx_string_put(mlx_ptr, win_ptr, 350, 900, 0xe6e6fa, "~To exit please press ESC~");
		mlx_key_hook(win_ptr, key_press, (void *)0);
		mlx_loop(mlx_ptr);
	}
	else if (argc < 2)
		write(1, "Usage: ./fdf.out [name_of_map]\n", 32);
	else
		return (-1);
}
