/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_handle_scene_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:38:14 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/14 12:06:27 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	handle_game_over(t_data *data);

int	handle_scene(t_data *data)
{
	if (!data->game_started)
	{
		if (!data->game_over)
		{
			if (data->mouse.enabled)
				toggle_mouse_control(data);
			render_menu(data);
		}
		else
		{
			render_game_over_screen(data);
			if (get_current_time() - data->game_over_time >= 3000)
				data->game_over = 0;
		}
		mlx_put_image_to_window(data->mlx,
			data->window, data->render_img, 0, 0);
		return (0);
	}
	handle_game_over(data);
	if (data->game_started)
		return (1);
	return (0);
}

static void	handle_game_over(t_data *data)
{
	if (data->player.current_health <= 0)
	{
		data->game_over_time = get_current_time();
		data->game_over = 1;
		data->game_started = 0;
	}
	else if (data->enemy.current_health <= 0)
	{
		data->game_over_time = get_current_time();
		data->game_over = 1;
		data->game_started = 0;
		data->player_won = 1;
	}
}
