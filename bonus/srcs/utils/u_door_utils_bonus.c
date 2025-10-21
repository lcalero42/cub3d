/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_door_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 02:26:59 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/21 02:29:11 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_door_pos_valid(t_data *data, t_pos door_pos)
{
	if (door_pos.y < 0 || door_pos.y >= data->grid.height)
		return (0);
	if (door_pos.x < 0 || door_pos.x >= data->grid.width)
		return (0);
	return (1);
}

int	sample_door_pixels(t_data *data, int x, int i, int sprite_bounds[2])
{
	int	sample_count;
	int	opaque_count;
	int	step_y;
	int	y;
	int	pixel;

	sample_count = 0;
	opaque_count = 0;
	step_y = (sprite_bounds[1] - sprite_bounds[0]) / 5;
	if (step_y < 1)
		step_y = 1;
	y = sprite_bounds[0];
	while (y < sprite_bounds[1])
	{
		pixel = get_door_pixel_at_position(data, x, y, i);
		if (pixel != -1)
		{
			sample_count++;
			if (!is_transparent_color(pixel))
				opaque_count++;
		}
		y += step_y;
	}
	return (sample_count > 0 && opaque_count * 2 > sample_count);
}
