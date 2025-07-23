/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/23 13:11:06 by lcalero          ###   ########.fr       */
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
		close_window(data);
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
	// printf("1\n");
	update_player_movement(data);
	// printf("2\n");
	trace_ray(data, data->player.angle);
	// printf("3\n");
	render_walls(data);
	// printf("4\n");
	mlx_put_image_to_window(data->mlx, data->window, data->render_img, 0, 0);
	// printf("x : %d, y : %d\n", (int)data->player.position.x, (int)data->player.position.y);
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
	if (parse_file(argv[1], &data))
		return (1);
	for (int i = 0; data.grid.grid[i]; i++)
		printf("%s\n", data.grid.grid[i]);
	data.mlx = mlx_init();
	data.player.position.x = 7.5;
	data.player.position.y = 7.5;
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
