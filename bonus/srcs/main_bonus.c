/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/25 15:10:40 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	render_loop(t_data *data)
{
	data->game_started = 1;
	update_player_movement(data);
	update_enemy_movement(data);
	trace_ray(data, data->player.angle);
	animation_routine(data);
	clear_screen(data);
	render_walls(data);
	if (data->render_fog)
		apply_fog_overlay(data);
	render_enemy_with_health(data, &data->enemy);
	render_crosshair(data);
	render_gun(data);
	render_health_bar(data, &data->health_bar);
	render_stamina(data, &data->stamina_bar);
	mlx_put_image_to_window(data->mlx, data->window, data->render_img, 0, 0);
	calculate_fps(data);
	render_minimap(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		u_print_error("missing map path");
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	init(&data, argv);
	mlx_hook(data.window, 2, 1L << 0, key_press_hook, &data);
	mlx_hook(data.window, 3, 1L << 1, key_release_hook, &data);
	mlx_hook(data.window, 6, (1L << 6), mouse_move, &data);
	mlx_hook(data.window, 17, 1L << 17, close_window, &data);
	mlx_mouse_hook(data.window, mouse_hook, &data);
	mlx_loop_hook(data.mlx, render_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
