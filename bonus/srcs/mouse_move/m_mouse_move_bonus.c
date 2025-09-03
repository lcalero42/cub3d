/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mouse_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:14:46 by ekeisler          #+#    #+#             */
/*   Updated: 2025/09/03 11:51:00 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}

static void	update_player_direction(t_data *data)
{
	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	data->player.camera_segment.x = -data->player.dir.y * CAMERA_PLANE_LENGTH;
	data->player.camera_segment.y = data->player.dir.x * CAMERA_PLANE_LENGTH;
}

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;
	int		delta_x;
	int		delta_y;
	double	rotation_amount_x;
	double	rotation_amount_y;
	int		center_x;
	int		center_y;

	data = (t_data *)param;
	if (!data || !data->mouse.enabled)
		return (0);
	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
	if (data->mouse.first_move)
	{
		data->mouse.last_x = center_x;
		data->mouse.last_y = center_y;
		data->mouse.first_move = 0;
		mlx_mouse_move(data->mlx, data->window, center_x, center_y);
		return (0);
	}
	delta_x = x - center_x;
	delta_y = y - center_y;
	if (abs(delta_x) <= 3 && abs(delta_y) <= 3)
		return (0);
	if (abs(delta_x) > 200 || abs(delta_y) > 200)
	{
		mlx_mouse_move(data->mlx, data->window, center_x, center_y);
		return (0);
	}
	rotation_amount_x = delta_x * data->mouse.sensitivity * 0.0008;
	rotation_amount_y = delta_y * data->mouse.sensitivity * 0.0008;
	if (abs(delta_x) > 20)
		rotation_amount_x *= 1.3;
	if (abs(delta_y) > 20)
		rotation_amount_y *= 1.3;
	data->player.angle += rotation_amount_x;
	data->player.pitch -= rotation_amount_y;
	if (data->player.pitch > PITCH_MAX)
		data->player.pitch = PITCH_MAX;
	else if (data->player.pitch < PITCH_MIN)
		data->player.pitch = PITCH_MIN;
	normalize_angle(&data->player.angle);
	update_player_direction(data);
	mlx_mouse_move(data->mlx, data->window, center_x, center_y);
	data->mouse.last_x = center_x;
	data->mouse.last_y = center_y;
	return (0);
}
