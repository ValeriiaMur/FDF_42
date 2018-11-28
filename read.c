/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:29:32 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/27 20:56:59 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void	to_coordinates(int massiv, t_point *point, t_map *map, int i, void *mlx_ptr, void *win_ptr)
{
	if (massiv == 0)
	{
		point[i].x = ((map->x_now - map->y_now) + map->stepx) * cos(0.523599);
		point[i].y = (map->y_now + map->x_now) * sin(0.523599);
	}
	else
	{
		point[i].x = ((map->x_now - map->y_now) + map->stepx) * cos(0.523599);
		point[i].y = -(massiv * 3) + (map->x_now + map->y_now) * sin(0.523599);
	}
	map->x_now = map->x_now + map->stepx;
	if (i > 0)
	{
		draw_x(point, mlx_ptr, win_ptr, i);
	}
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
