/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mouse_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:37:21 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/07 14:40:03 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	apply_rotation_with_limits(t_data *data, int smooth_x, int smooth_y)
{
	double	rotation_amount_x;
	double	rotation_amount_y;
	double	new_pitch;

	rotation_amount_x = smooth_x * data->mouse.sensitivity * 0.0015;
	rotation_amount_y = smooth_y * data->mouse.sensitivity * 0.0015;
	data->player.angle += rotation_amount_x;
	new_pitch = data->player.pitch - rotation_amount_y;
	if (new_pitch > PITCH_MAX)
		data->player.pitch = PITCH_MAX;
	else if (new_pitch < PITCH_MIN)
		data->player.pitch = PITCH_MIN;
	else
		data->player.pitch = new_pitch;
}

void	update_player_direction(t_data *data)
{
	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	data->player.camera_segment.x = -data->player.dir.y * CAMERA_PLANE_LENGTH;
	data->player.camera_segment.y = data->player.dir.x * CAMERA_PLANE_LENGTH;
}

void	add_to_smooth_buffer(t_data *data, int delta_x, int delta_y)
{
	data->mouse.m_smooth.buffer_x[data->mouse.m_smooth.buffer_index] = delta_x;
	data->mouse.m_smooth.buffer_y[data->mouse.m_smooth.buffer_index] = delta_y;
	data->mouse.m_smooth.buffer_index = (data->mouse.m_smooth.buffer_index + 1) % 5;
	if (!data->mouse.m_smooth.buffer_filled 
		&& data->mouse.m_smooth.buffer_index == 0)
		data->mouse.m_smooth.buffer_filled = 1;
}

void	get_smoothed_delta(t_data *data, int *smooth_x, int *smooth_y)
{
	int	i;
	int	count;

	*smooth_x = 0;
	*smooth_y = 0;
	count = data->mouse.m_smooth.buffer_filled ? 5 : 
		data->mouse.m_smooth.buffer_index;
	i = 0;
	while (i < count)
	{
		*smooth_x += data->mouse.m_smooth.buffer_x[i];
		*smooth_y += data->mouse.m_smooth.buffer_y[i];
		i++;
	}
	if (count > 0)
	{
		*smooth_x /= count;
		*smooth_y /= count;
	}
}