/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:52:10 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/23 11:10:37 by vmuradia         ###   ########.fr       */
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
 	double z;
 	int color;
 }				t_point;

typedef struct			s_map
{
	double				width;
	double				height;
	double				stepx;
	double 				stepy;
	double				total;
}						t_map;

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



void		read_map(char *file, void *mlx_ptr, void *win_ptr)
{
	t_map *map;
	map = (t_map*)ft_memalloc(sizeof(t_map));
	int fd;
	char *line;
	int res;
	double x = 0;
	double y = 0;
	int i = 0;
	int j;
	char ***massiv;
	int x0, y0;
	t_point *point;

	int jopa;
	jopa = 0;
	fd = open(file, O_RDONLY);
	massiv = (char***)malloc(sizeof(char*)*3);
	while((res = get_next_line(fd, &line)) == 1)
	{
		massiv[jopa] = ft_strsplit(line, ' ');
		jopa++;
		ft_putendl(line);
		x = ft_count_words(line, ' ');
		y++;
	}
	map->height = y;
	map->width = x;
	map->stepx = 300/x;
	map->stepy = 300/y;
	map->total = x * y;
	point = (t_point*)malloc(sizeof(t_point) * map->total);
	int k = -1;
	while (massiv[++k] && k < y)
	{
		jopa = 0;
		while (massiv[k][jopa])
		{
			ft_putstr(massiv[k][jopa]);
			jopa++;
		}
	}
	// printf("This is x: %d and y: %d \n", map->width, map->height, map->stepx);
	while (i < map->height)
	{
		j = 0;
		x = 0;
		while (j < map->width)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xffd700);
			x = x + map->stepx;
			j++;
		}
		y = y+map->stepy;
		i++;
		//drawline(x, y, x0, y0, mlx_ptr, win_ptr);
	}

}



int main(int argc, char **argv)
{
//	int 			fd;
//	char 			*line;
//	t_map			*map;
	void 			*mlx_ptr;
	void 			*win_ptr;
//	char 			**massiv;

//	massiv = NULL;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Some Shit");
	read_map(argv[1], mlx_ptr, win_ptr);
	mlx_loop(mlx_ptr);
	//mlx_string_put(mlx_ptr, win_ptr, 100, 450, 0xffd700, "Fuck you");
//	if (argc == 2)
//	{
//		if ((fd = open(argv[1], O_RDONLY)) <= 0)
//			return (-1);
//		map = map_init();
//		if (read_map(fd, line) == -1)
//			return (-1);

return 0;

}
