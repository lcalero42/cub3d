/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mouse_rotation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:16:21 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/08 17:25:54 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_recenter(t_data *data, int force)
{
	data->mouse.recenter_frame_counter++;
	if (force || data->mouse.recenter_frame_counter >= 4)
	{
		mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
			data->mouse.center_y);
		data->mouse.recenter_frame_counter = 0;
	}
}

void	mouse_rotation(int delta_x, int delta_y, t_data *data)
{
	int		smooth_x;
	int		smooth_y;
	double	magnitude;
	int		force_recenter;

	magnitude = sqrt(delta_x * delta_x + delta_y * delta_y);
	force_recenter = 0;
	if (abs(delta_y) > 60 || abs(delta_x) > 80)
		force_recenter = 1;
	if (magnitude > 100 && force_recenter)
		mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
			data->mouse.center_y);
	clamp_delta(&delta_x, &delta_y, magnitude);
	add_to_smooth_buffer(data, delta_x, delta_y);
	get_smoothed_delta(data, &smooth_x, &smooth_y);
	apply_rotation_with_limits(data, smooth_x, smooth_y);
	norm_angle(&data->player.angle, data);
	update_player_direction(data);
	handle_recenter(data, force_recenter);
}

void	norm_angle(double *angle, t_data *data)
{
	(void)data;
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}
