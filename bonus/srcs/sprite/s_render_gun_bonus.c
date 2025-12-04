/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_render_gun_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:52:11 by lcalero           #+#    #+#             */
/*   Updated: 2025/12/04 18:24:32 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		draw_gun_at(t_data *data, t_render *render,
					t_sprite_bounds *bounds);

void	render_gun(t_data *data)
{
	t_sprite_bounds	bounds;
	int				gun_width;
	int				gun_height;

	gun_width = WINDOW_WIDTH * 0.7;
	gun_height = WINDOW_HEIGHT * 0.7;
	bounds.start_x = (WINDOW_WIDTH - gun_width) >> 1;
	bounds.end_x = bounds.start_x + gun_width - 1;
	bounds.sprite_top = WINDOW_HEIGHT - gun_height;
	bounds.sprite_height = gun_height;
	bounds.half_width = gun_width >> 1;
	bounds.sprite_size = 64;
	if (data->gun.is_playing)
		draw_gun_at(data, &data->gun.render_arr[data->gun.index], &bounds);
	else if (data->shot.is_playing)
		draw_gun_at(data, &data->shot.render_arr[data->shot.index], &bounds);
}

static void	draw_gun_at(t_data *data, t_render *render,
		t_sprite_bounds *bounds)
{
	t_sprite_params	params;
	int				x;
	int				screen_x;

	params = init_sprite_params(&render->info, bounds->sprite_top,
			bounds->sprite_height);
	x = bounds->start_x - data->player.pitch;
	screen_x = (WINDOW_WIDTH >> 1) + (WINDOW_WIDTH * 0.1);
	while (x <= bounds->end_x)
	{
		params.tex_x = (int)((float)((x - (screen_x - bounds->half_width)) * 64)
				/ bounds->sprite_height);
		if (params.tex_x < 0)
			params.tex_x = 0;
		if (params.tex_x >= 64)
			params.tex_x = 64 - 1;
		params.x = x;
		draw_sprite_column(data, &params, bounds);
		x++;
	}
}
