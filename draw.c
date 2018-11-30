/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:29:59 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/28 19:32:47 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** Naive algorithm for connecting dots horizontally (x)
*/

void	draw_x(t_point *point, int i, t_map *map)
{
	int dx;
	int	dy;
	int	x;
	int	y;

	dx = point[i].x - point[i - 1].x;
	dy = point[i].y - point[i - 1].y;
	x = point[i - 1].x;
	while (point[i].x > x)
	{
		y = point[i - 1].y + dy * (x - point[i - 1].x) / dx;
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, 500 + x, 200 + y, map->color);
		x++;
	}
}

/*
** Helper for draw_y
*/

void	draw_init(t_point *point, int counter, int prev_y, t_map *map)
{
	map->dy = abs(point[prev_y].y - point[counter].y);
	map->dx = abs(point[prev_y].x - point[counter].x);
	map->sx = point[prev_y].x >= point[counter].x ? 1 : -1;
	map->sy = point[prev_y].y >= point[counter].y ? 1 : -1;
}

/*
** First part of Bresenham Algortithm
*/

void	draw_first(t_point *point, int counter, t_map *map)
{
	int x;
	int y;

	map->d = (map->dy << 1) - map->dx;
	map->d1 = map->dy << 1;
	map->d2 = (map->dy - map->dx) << 1;
	mlx_pixel_put(map->mlx_ptr, map->win_ptr, 500 + point[counter].x,
		200 + point[counter].y, map->color);
	y = point[counter].y + map->sy;
	x = point[counter].x;
	while (map->i <= map->dx)
	{
		if (map->d > 0)
		{
			map->d += map->d2;
			y += map->sy;
		}
		else
			map->d += map->d1;
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, 500 + x, 200 + y,
			map->color);
		map->i++;
		x += map->sx;
	}
}

/*
** The function itself
*/

void	draw_y(t_point *point, int counter, int prev_y, t_map *map)
{
	map->i = 1;
	draw_init(point, counter, prev_y, map);
	if (map->dy <= map->dx)
	{
		draw_first(point, counter, map);
	}
	else
		keep_drawing(point, counter, map);
}

/*
** Second part of draw_y
*/

void	keep_drawing(t_point *point, int counter, t_map *map)
{
	int y;
	int x;

	map->d = (map->dx << 1) - map->dy;
	map->d1 = map->dx << 1;
	map->d2 = (map->dx - map->dy) << 1;
	mlx_pixel_put(map->mlx_ptr, map->win_ptr, 500 + point[counter].x,
		200 + point[counter].y, map->color);
	y = point[counter].y + map->sy;
	x = point[counter].x;
	map->i = 1;
	while (map->i <= map->dy)
	{
		if (map->d > 0)
		{
			map->d += map->d2;
			x += map->sx;
		}
		else
			map->d += map->d1;
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, 500 + x, 200 + y, map->color);
		map->i++;
		y += map->sy;
	}
}
