/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render_game_over_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:48:21 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/14 12:06:57 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_game_over_screen(t_data *data)
{
	int				button_width;
	int				button_height;
	int				start_y;
	long long		die_time;

	render_background(data);
	button_width = WINDOW_WIDTH * 0.5;
	button_height = WINDOW_HEIGHT * 0.5;
	start_y = (WINDOW_HEIGHT - (button_height * 2)) / 2;
	data->game_over_bounds.start_x = (WINDOW_WIDTH - button_width) / 2;
	data->game_over_bounds.end_x = data->game_over_bounds.start_x
		+ button_width;
	data->game_over_bounds.sprite_top = start_y;
	data->game_over_bounds.sprite_height = button_height;
	data->game_over_bounds.half_width = button_width / 2;
	data->game_over_bounds.sprite_size = 128;
	die_time = get_current_time();
	if (data->player_won)
		draw_button_at(data, &data->you_won_print, &data->game_over_bounds);
	else
		draw_button_at(data, &data->game_over_print, &data->game_over_bounds);
}

void	reset_game(t_data *data)
{
	spawn_enemy(data);
	init_door_system(data);
	data->game_started = 1;
	toggle_mouse_control(data);
	find_player_pos(data);
}
