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
 	int x;
 	int y;
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

void		read_map(char *file, void *mlx_ptr, void *win_ptr)
{
	t_map *map;
	map = (t_map*)ft_memalloc(sizeof(t_map));
	int fd;
	char *line;
	double x = 0;
	double y = 0;
	int j;
	char ***massiv;
  int numbers[100];
	int i = 0;
	t_point *point;
  double len = 0;
  double height;

	fd = open(file, O_RDONLY);
  massiv = (char***)malloc(sizeof(char*) * 3);
	while(get_next_line(fd, &line) == 1)
	{
		massiv[i] = ft_strsplit(line, ' ');
		i++;
		ft_putendl(line);
		len = ft_count_words(line, ' ');
		height++;
	}
	map->height = height;
	map->width = len;
	map->stepx = 300/len;
	map->stepy = 300/height;
	map->total = len * height;
  int p = 0;
  int k = -1;
  while(massiv[++k] && k < height)
  {
   i = -1;
    while(massiv[k][++i])
    {
      numbers[p] = ft_atoi(massiv[k][i]);
      p++;
    }
  }
  //printf("This is 10:%d and 11: %d, and 12:%d", numbers[10], numbers[11], numbers[12]);
  point->x = 100;
  point->y = 100;
  int counter = 0;
  while (counter <= map->height)
  {
    j = 0;
    while(j < map->width)
    {
      point->x = point->x +map->stepx;
    }
  }

}


int main(int argc, char **argv)
{

	void 			*mlx_ptr;
	void 			*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Some Shit");
	read_map(argv[1], mlx_ptr, win_ptr);
	mlx_loop(mlx_ptr);
}
