/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:52:10 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/25 18:19:11 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./libft/libft.h"
#include <fcntl.h>

 typedef struct s_point
 {
 	double x;
 	double y;
 }				t_point;

typedef struct			s_map
{
	double				width;
	double				height;
	double				stepx;
	double 				stepy;
	double				total;
	double				x_now;
	double				y_now;
}						t_map;


void drawline(t_point *point, t_map *map, void *mlx_ptr, void *win_ptr, int i)
{
	int dx, dy, f, x, y;
	dx = point[i].x - point[i-1].x;
	dy = point[i].y - point[i-1].y;
	f = dx / 2;
	// printf("this is dx:%d and dy:%d and f:%d\n", dx, dy, f);
	// printf("This is x0 and y0: %f %f NOW x1 and y1: %f %f", point[i-1].x, point[i].x, point[i-1].y, point[i].y);
  x = point[i - 1].x;

  while (point[i].x > x)
	{
    y = point[i - 1].y + dy * (x - point[i - 1].x) / dx;
		mlx_pixel_put(mlx_ptr, win_ptr, 450 + x, 400 + y, 0xffd700);
		// if (f < 0)
		// {
		// 	f = f + dx;
		// }
		// else
		// {
		// 	f = f - dy;
		// 	point[i-1].y++;
		// }
		x++;
	}
}


void to_coordinates(int massiv, t_point *point, t_map *map, int i, void *mlx_ptr, void *win_ptr )
{
	int dx, dy;
	int counter = 0;
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
	mlx_pixel_put(mlx_ptr, win_ptr, 450 + point[i].x, 400 + point[i].y, 0xffd700);
	if (i > 0)
	{
		drawline(point, map, mlx_ptr, win_ptr, i);
	}
	// printf("This is x %f and y %f and i is : %d\n", point[i].x, point[i].y, i);
}

void map_init(t_map *map, double x, double y)
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
	double x = 0;
	double y = 0;
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
	mlx_string_put(mlx_ptr, win_ptr, 400, 100, 0xffd700, "Welcome to FDF");
	mlx_loop(mlx_ptr);
	}
}
