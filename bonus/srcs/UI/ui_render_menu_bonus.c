/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render_menu_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:40:43 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/24 15:45:59 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_button_at(t_data *data, t_render *render,
				t_sprite_bounds *bounds);

static void	draw_button_at(t_data *data, t_render *render,
				t_sprite_bounds *bounds)
{
	t_sprite_params	params;
	int				x;
	int				texture_width;
	int				texture_height;

	texture_width = bounds->sprite_size;
	texture_height = bounds->sprite_size;
	params = init_sprite_params(&render->info, bounds->sprite_top,
			bounds->sprite_height);
	x = bounds->start_x;
	while (x <= bounds->end_x)
	{
		params.tex_x = (int)(((float)(x - bounds->start_x)
					/ (float)(bounds->end_x - bounds->start_x))
				* texture_width);
		if (params.tex_x < 0)
			params.tex_x = 0;
		if (params.tex_x >= texture_width)
			params.tex_x = texture_width - 1;
		params.x = x;
		draw_sprite_column(data, &params, bounds);
		x++;
	}
}

static void	render_background(t_data *data)
{
	t_sprite_bounds	bg_bounds;

	bg_bounds.start_x = 0;
	bg_bounds.end_x = WINDOW_WIDTH;
	bg_bounds.sprite_top = 0;
	bg_bounds.sprite_height = WINDOW_HEIGHT;
	bg_bounds.half_width = WINDOW_WIDTH / 2;
	bg_bounds.sprite_size = 128;
	draw_button_at(data, &data->menu_background, &bg_bounds);
}

int	handle_menu_button_clicks(t_data *data, int mouse_x, int mouse_y)
{
	t_sprite_bounds	play_bounds;
	t_sprite_bounds	leave_bounds;

	play_bounds = data->play_bounds;
	leave_bounds = data->leave_bounds;
	if (mouse_x >= play_bounds.start_x && mouse_x <= play_bounds.end_x
		&& mouse_y >= play_bounds.sprite_top
		&& mouse_y <= play_bounds.sprite_top + play_bounds.sprite_height)
	{
		data->game_started = 1;
		return (1);
	}
	if (mouse_x >= leave_bounds.start_x && mouse_x <= leave_bounds.end_x
		&& mouse_y >= leave_bounds.sprite_top
		&& mouse_y <= leave_bounds.sprite_top + leave_bounds.sprite_height)
	{
		close_window(data);
		return (2);
	}
	return (0);
}

/**
 * @brief Render both play and leave buttons on screen with proper positioning
 * @param data Main data structure
 */
void	render_menu(t_data *data)
{
	int				button_width;
	int				button_height;
	int				button_spacing;
	int				start_y;

	render_background(data);
	button_width = WINDOW_WIDTH * 0.5;
	button_height = WINDOW_HEIGHT * 0.5;
	button_spacing = button_height * 0.1;
	start_y = (WINDOW_HEIGHT - (button_height * 2) + button_spacing) / 2;
	data->play_bounds.start_x = (WINDOW_WIDTH - button_width) / 2;
	data->play_bounds.end_x = data->play_bounds.start_x + button_width;
	data->play_bounds.sprite_top = start_y + button_spacing;
	data->play_bounds.sprite_height = button_height;
	data->play_bounds.half_width = button_width / 2;
	data->play_bounds.sprite_size = 128;
	draw_button_at(data, &data->play_button, &data->play_bounds);
	data->leave_bounds.start_x = (WINDOW_WIDTH - button_width) / 2;
	data->leave_bounds.end_x = data->leave_bounds.start_x + button_width;
	data->leave_bounds.sprite_top = start_y + button_height - button_spacing;
	data->leave_bounds.sprite_height = button_height;
	data->leave_bounds.half_width = button_width / 2;
	data->leave_bounds.sprite_size = 128;
	draw_button_at(data, &data->leave_button, &data->leave_bounds);
}
