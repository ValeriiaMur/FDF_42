/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:28:17 by vmuradia          #+#    #+#             */
/*   Updated: 2018/11/27 20:44:44 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;

	if (argc == 2)
	{
		map = (t_map*)malloc(sizeof(t_map));
		mlx_ptr = mlx_init();
		win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "My FDF");
		read_map(argv[1], map, mlx_ptr, win_ptr);
		mlx_string_put(mlx_ptr, win_ptr, 400, 100, 0xe6e6fa, "Welcome to FDF");
		mlx_string_put(mlx_ptr, win_ptr, 350, 900, 0xe6e6fa,
			"To exit please press ESC");
		mlx_key_hook(win_ptr, key_press, (void *)0);
		mlx_loop(mlx_ptr);
	}
	else if (argc < 2)
		write(1, "Usage: ./fdf.out [name_of_map]\n", 32);
	else
		return (-1);
}
