/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/26 18:15:16 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release_hook(int keycode, t_data *data)
{
	if (keycode == XK_d || keycode == XK_d
		|| keycode == XK_d || keycode == XK_d)
		data->player.is_moving = 0;
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
	if (keycode == XK_d || keycode == XK_a
		|| keycode == XK_w || keycode == XK_s)
		data->player.is_moving = 1;
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
	data->game_started = 1;
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
		if (argc == 1)
			u_print_error("Missing map path");
		if (argc > 2)
			u_print_error("Too much parameters");
		return (1);
	}
	validate_window_size();
	ft_bzero(&data, sizeof(t_data));
	init(&data, argv);
	mlx_hook(data.window, 2, 1L << 0, key_press_hook, &data);
	mlx_hook(data.window, 3, 1L << 1, key_release_hook, &data);
	mlx_hook(data.window, 17, 1L << 17, close_window, &data);
	mlx_loop_hook(data.mlx, render_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
