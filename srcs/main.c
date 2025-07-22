/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/22 13:37:02 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release_hook(int keycode, t_data *data)
{
	if (keycode == XK_d)
		data->keys.d = 0;
	if (keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_Up)
		data->keys.up = 0;
	if (keycode == XK_Down)
		data->keys.down = 0;
	if (keycode == XK_Right)
		data->keys.right = 0;
	if (keycode == XK_Left)
		data->keys.left = 0;
	return (0);
}

int	key_press_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_image(data->mlx, data->render_img);
		mlx_destroy_image(data->mlx, data->north_wall.wall_texture_img);
		mlx_destroy_image(data->mlx, data->south_wall.wall_texture_img);
		mlx_destroy_image(data->mlx, data->east_wall.wall_texture_img);
		mlx_destroy_image(data->mlx, data->west_wall.wall_texture_img);
		mlx_destroy_window(data->mlx, data->window);
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	if (keycode == XK_d)
		data->keys.d = 1;
	if (keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_Up)
		data->keys.up = 1;
	if (keycode == XK_Down)
		data->keys.down = 1;
	if (keycode == XK_Right)
		data->keys.right = 1;
	if (keycode == XK_Left)
		data->keys.left = 1;
	return (0);
}

int	render_loop(t_data *data)
{
	update_player_movement(data);
	trace_ray(data, data->player.angle);
	render_walls(data);
	mlx_put_image_to_window(data->mlx, data->window, data->render_img, 0, 0);
	usleep(5000);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("error : missing map path\n");
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	if (1 == parse_file(argv[1], &data))
	{
		return (1);
	}
	data.mlx = mlx_init();
	data.player.position.x = 2.5;
	data.player.position.y = 2.5;
	data.window = mlx_new_window(data.mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	init_walls(&data);
	mlx_hook(data.window, 2, 1L << 0, key_press_hook, &data);
	mlx_hook(data.window, 3, 1L << 1, key_release_hook, &data);
	mlx_loop_hook(data.mlx, render_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
