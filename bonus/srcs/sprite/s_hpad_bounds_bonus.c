/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_hpad_bounds_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:01:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/21 02:42:23 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_sprite_bounds_y(t_data *data, t_sprite_calc *calc)
{
	calc->draw_start_y = -calc->sprite_height / 2 + WINDOW_HEIGHT / 2
		+ (int)data->player.pitch_offset;
	if (calc->draw_start_y < 0)
		calc->draw_start_y = 0;
	calc->draw_end_y = calc->sprite_height / 2 + WINDOW_HEIGHT / 2
		+ (int)data->player.pitch_offset;
	if (calc->draw_end_y >= WINDOW_HEIGHT)
		calc->draw_end_y = WINDOW_HEIGHT - 1;
}

void	calculate_sprite_bounds_x(t_sprite_calc *calc)
{
	calc->draw_start_x = -calc->sprite_width / 2 + calc->screen_x;
	if (calc->draw_start_x < 0)
		calc->draw_start_x = 0;
	calc->draw_end_x = calc->sprite_width / 2 + calc->screen_x;
	if (calc->draw_end_x >= WINDOW_WIDTH)
		calc->draw_end_x = WINDOW_WIDTH - 1;
}

void	render_sprite(t_data *data, t_generic_sprite *sprite)
{
	if (sprite->type == SPRITE_ENEMY)
		render_enemy_with_health(data, &data->enemy);
	else if (sprite->type == SPRITE_HEALTH_PAD)
		render_health_pad_sprite(data, (t_health_pad *)sprite->data,
			&sprite->calc);
}
