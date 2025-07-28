/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/28 17:49:03 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release_hook(int keycode, t_data *data)
{
	if (keycode == XK_d)
		data->keys.d = 0;
	if (keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_w)
		data->keys.w = 0;
	if (keycode == XK_s)
		data->keys.s = 0;
	if (keycode == XK_Right)
		data->keys.right = 0;
	if (keycode == XK_Left)
		data->keys.left = 0;
	return (0);
}

int	key_press_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	if (keycode == XK_f && data->render_fog)
		data->render_fog = 0;
	else if (keycode == XK_f && !data->render_fog)
		data->render_fog = 1;
	if (keycode == XK_d)
		data->keys.d = 1;
	if (keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_w)
		data->keys.w = 1;
	if (keycode == XK_s)
		data->keys.s = 1;
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
	clear_screen(data);
	render_walls(data);
	if (data->render_fog)
		apply_fog_overlay(data);
	mlx_put_image_to_window(data->mlx, data->window, data->render_img, 0, 0);
	calculate_fps(data);
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
	data.render_fog = 1;
	if (parse_file(argv[1], &data))
		return (1);
	data.mlx = mlx_init();
	find_player_pos(&data);
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
	init_walls(&data);
	mlx_hook(data.window, 2, 1L << 0, key_press_hook, &data);
	mlx_hook(data.window, 3, 1L << 1, key_release_hook, &data);
	mlx_hook(data.window, 17, 1L << 17, close_window, &data);
	mlx_loop_hook(data.mlx, render_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
