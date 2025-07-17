/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/17 19:20:21 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx, data->render_img);
		mlx_destroy_image(data->mlx, data->wall_texture_img);
		mlx_destroy_window(data->mlx, data->window);
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	determine_movement(keycode, data);
	return (0);
}

int	render_loop(t_data *data)
{
	trace_ray(data, data->player.angle);
	render_walls(data);
	mlx_put_image_to_window(data->mlx, data->window, data->render_img, 0, 0);
	return (1);
}

int	main(void)
{
	t_data	data;
	
	static char *grid_map[] = {
		"111111",
		"100001", 
		"102101",
		"100001",
		"111111",
		NULL
	};
	ft_bzero(&data, sizeof(t_data));
	data.grid.grid = grid_map;
	data.mlx = mlx_init();
	data.player.position.x = 2.5;
	data.player.position.y = 2.5;
	data.window = mlx_new_window(data.mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	init_walls(&data);
	mlx_hook(data.window, 2, 1L << 0, key_hook, &data);
	mlx_loop_hook(data.mlx, render_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
