/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:52:10 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/23 22:39:48 by vmuradia         ###   ########.fr       */
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

void drawline(double x0, double y0, double x1, double y1, void *mlx_ptr, void *win_ptr)
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

void to_coordinates(int massiv, t_point *point, t_map *map, int i, void *mlx_ptr, void *win_ptr )
{
	if (massiv == 0)
	{
		point[i].x = map->x_now + map->stepx;
		point[i].y = map->y_now;
	}
	else
	{
		point[i].x = map->x_now + map->stepx;
		point[i].y = map->y_now - (massiv * 3);
	}
	map->x_now = map->x_now + map->stepx;
	mlx_pixel_put(mlx_ptr, win_ptr, point[i].x, point[i].y, 0xffd700);
	drawline(point[i].x, point[i].y, map->x_now, map->y_now, mlx_ptr, win_ptr);
	printf("This is x %f and y %f and i is : %d\n", point[i].x, point[i].y, i);
}

void		read_map(char *file, t_map *map, void *mlx_ptr, void *win_ptr)
{
	int fd;
	char *line;
	int res;
	double x = 0;
	double y = 0;
	int i = 0;
	int j;
	char **massiv;
	int x0, y0;
	t_point *point;

	int jopa;
	jopa = 0;
	fd = open(file, O_RDONLY);
	while((res = get_next_line(fd, &line)) == 1)
	{
		//massiv = ft_strsplit(line, ' ');
	//	ft_putendl(line);
		x = ft_count_words(line, ' ');
		y++;
	}
	free(line);
	close(fd);
	map->height = y;
	map->width = x;
	map->stepx = 500/x;
	map->stepy = 500/y;
	map->total = x * y;
	point = (t_point*)malloc(sizeof(t_point) * map->total);
	map->x_now = 100 - map->stepx;
	map->y_now = 100;
	int fd1;
	fd1 = open(file, O_RDONLY);
	int nums;
	while((nums = get_next_line(fd1, &line)) == 1)
	{
		//printf("sadsadasdasdasdas\n");
		massiv = ft_strsplit(line, ' ');
		int a = 0;
		while(a < map->width)
		{
			to_coordinates(ft_atoi(massiv[a]), point, map, i, mlx_ptr, win_ptr);
			i++;
			a++;
		}
		a = 0;
		printf("\n" );
		map->x_now = 100 - map->stepx;
		map->y_now = map->y_now + map->stepy;
	}
	// int k = -1;
	// while (massiv[++k] && k < y)
	// {
	// 	jopa = 0;
	// 	while (massiv[k][jopa])
	// 	{
	// 		ft_putstr(&massiv[k][jopa]);
	// 		jopa++;
	// 	}
	// }
	// while (i < map->height)
	// {
	// 	j = 0;
	// 	x = 100;
	// 	while (j < map->width)
	// 	{
	// 		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xffd700);
	// 		point->x = x;
	// 		point->y = y;
	// 		printf("This is x: %f and y: %f \n", point->x, point->y);
	// 		x = x + map->stepx;
	// 		j++;
	// 	}
	// 	printf("AGAIN This is x: %f and y: %f \n", point->x, point->y);
	// 	y = y+map->stepy;
	// 	i++;
	// }
}



int main(int argc, char **argv)
{
//	int 			fd;
//	char 			*line;
//	t_map			*map;
	void 			*mlx_ptr;
	void 			*win_ptr;
	t_map			*map;
//	char 			**massiv;

	map = (t_map*)malloc(sizeof(t_map));
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "Some Shit");
	read_map(argv[1], map, mlx_ptr, win_ptr);


	mlx_loop(mlx_ptr);
	//mlx_string_put(mlx_ptr, win_ptr, 100, 450, 0xffd700, "Fuck you");
//	if (argc == 2)
//	{
//		if ((fd = open(argv[1], O_RDONLY)) <= 0)
//			return (-1);
//		map = map_init();
//		if (read_map(fd, line) == -1)
//			return (-1);
}
