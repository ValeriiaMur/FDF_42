/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:19 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/28 15:22:28 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_map
{
	int			width;
	int			height;
	int			stepx;
	int			stepy;
	int			total;
	int			x_now;
	int			y_now;
	void		*mlx_ptr;
	void		*win_ptr;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			d;
	int			d1;
	int			d2;
	int			i;
}				t_map;

void			draw_x(t_point *point, int i, t_map *map);
int				key_press(int key, void *param);
void			connect_line(t_point *point, t_map *map);
void			to_coordinates(int massiv, t_point *point, t_map *map, int i);
void			map_init(t_map *map, int x, int y);
void			read_map(char *file, t_map *map, int fd, char *line);
void			get_info(char *file, t_map *map, int fd, char *line);
void			draw_init(t_point *point, int counter, int prev_y, t_map *map);
void			keep_drawing(t_point *point, int counter, t_map *map);
void			draw_y(t_point *point, int counter, int prev_y, t_map *map);
void			draw_first(t_point *point, int counter, t_map *map);

#endif
