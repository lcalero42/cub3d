/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_render_gun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:52:11 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/04 16:08:05 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_gun(t_data *data)
{
	t_sprite_bounds	bounds;

	calculate_sprite_bounds(0, 64, &bounds);
	bounds.sprite_height = WINDOW_HEIGHT * 0.4;
	bounds.sprite_top = WINDOW_HEIGHT * 0.4;
	draw_sprite_at(data, &data->gun, &bounds, &data->enemy);
}
