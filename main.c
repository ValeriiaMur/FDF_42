/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:28:17 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/28 15:18:17 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	int		fd;
	char	*line;

	fd = 0;
	line = NULL;
	if (argc == 2)
	{
		map = (t_map*)malloc(sizeof(t_map));
		map->mlx_ptr = mlx_init();
		map->win_ptr = mlx_new_window(map->mlx_ptr, 1000, 1000, "My FDF");
		read_map(argv[1], map, fd, line);
		mlx_string_put(map->mlx_ptr, map->win_ptr, 400, 100, 0xe6e6fa,
			"Welcome to FDF");
		mlx_string_put(map->mlx_ptr, map->win_ptr, 350, 900, 0xe6e6fa,
			"To exit please press ESC");
		mlx_key_hook(map->win_ptr, key_press, (void *)0);
		mlx_loop(map->mlx_ptr);
	}
	else if (argc < 2)
		write(1, "Usage: ./fdf [name_of_map]\n", 27);
	else
		return (-1);
}
norminette
/*
** Close with esc
*/

int	key_press(int key, void *param)
{
	(void)param;
	if (key == 53)
	{
		exit(1);
	}
	return (0);
}
