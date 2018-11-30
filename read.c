/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:29:32 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/30 09:14:15 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** Transfer to coordinates here, iso porjection, draw on x
*/

void	to_coordinates(int massiv, t_point *point, t_map *map, int i)
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
		draw_x(point, i, map);
	rainbow(map, massiv);
}

void	map_init(t_map *map, int x, int y)
{
	map->height = y;
	map->width = x;
	map->stepx = 500 / x;
	map->stepy = 500 / y;
	map->total = x * y;
	map->x_now = 100 - map->stepx;
	map->y_now = 100;
}

/*
** Read file 2ns time to transfer to coordinates
*/

void	read_map(char *file, t_map *map, int fd, char *line)
{
	int		i;
	int		a;
	char	**massiv;
	t_point *point;

	i = 0;
	a = 0;
	get_info(file, map, fd, line);
	point = (t_point*)malloc(sizeof(t_point) * map->total);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		massiv = ft_strsplit(line, ' ');
		while (a < map->width)
		{
			to_coordinates(ft_atoi(massiv[a]), point, map, i);
			i++;
			a++;
		}
		a = 0;
		map->x_now = 100 - map->stepx;
		map->y_now = map->y_now + map->stepy;
	}
	connect_line(point, map);
	free(point);
}

/*
** Read file for the 1st time to transfer to get width and lengt, map init.
*/

void	get_info(char *file, t_map *map, int fd, char *line)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		x = ft_count_words(line, ' ');
		y++;
	}
	free(line);
	close(fd);
	map_init(map, x, y);
}

/*
** Connect coordinates on y (using Bresenham's). My logic is to jump on a next
** row by substracting width of the map. The first row < 0 and is not connected
** with the dots up.
*/

void	connect_line(t_point *point, t_map *map)
{
	int counter;
	int prev_y;

	counter = 0;
	while (counter < map->total)
	{
		prev_y = counter - map->width;
		if (prev_y >= 0)
		{
			draw_y(point, counter, prev_y, map);
		}
		counter++;
	}
}
