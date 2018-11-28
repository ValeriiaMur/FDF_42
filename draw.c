/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:29:59 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/27 20:30:18 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

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

int key_press(int key,void *param)
{
	(void)param;
	if (key == 53)
	{
		exit(1);
	}
	return (0);
}

void draw_line(int x0, int y0, int x1, int y1, void *mlx_ptr, void *win_ptr)
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
			draw_line(point[counter].x, point[counter].y, point[prev_y].x, point[prev_y].y, mlx_ptr, win_ptr);
		}
		counter++;
	}
}
