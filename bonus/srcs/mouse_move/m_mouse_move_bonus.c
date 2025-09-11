/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mouse_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:14:46 by ekeisler          #+#    #+#             */
/*   Updated: 2025/09/11 16:15:06 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	mouse_rotation(int center_x, int center_y, t_data *data);
static void	normalize_angle(double *angle, t_data *data);
static void	update_player_direction(t_data *data);

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data || !data->mouse.enabled)
		return (0);
	data->mouse.center_x = WINDOW_WIDTH / 2;
	data->mouse.center_y = WINDOW_HEIGHT / 2;
	if (data->mouse.first_move)
	{
		data->mouse.first_move = 0;
		mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
			data->mouse.center_y);
		return (0);
	}
	data->mouse.delta_x = x - data->mouse.center_x;
	data->mouse.delta_y = y - data->mouse.center_y;
	mouse_rotation(data->mouse.delta_x, data->mouse.delta_y, data);
	return (0);
}

static void	mouse_rotation(int delta_x, int delta_y, t_data *data)
{
	double	rotation_amount_x;
	double	rotation_amount_y;

	if (abs(delta_x) <= 3 && abs(delta_y) <= 3)
		return ;
	if (abs(delta_x) > 200 || abs(delta_y) > 200)
	{
		mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
			data->mouse.center_y);
		return ;
	}
	rotation_amount_x = delta_x * data->mouse.sensitivity * 0.0008;
	rotation_amount_y = delta_y * data->mouse.sensitivity * 0.0008;
	if (abs(delta_x) > 20)
		rotation_amount_x *= 1.3;
	if (abs(delta_y) > 20)
		rotation_amount_y *= 1.3;
	data->player.angle += rotation_amount_x;
	data->player.pitch -= rotation_amount_y;
	normalize_angle(&data->player.angle, data);
	update_player_direction(data);
	mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
		data->mouse.center_y);
	data->mouse.last_x = data->mouse.center_x;
	data->mouse.last_y = data->mouse.center_y;
}

static void	normalize_angle(double *angle, t_data *data)
{
	if (data->player.pitch > PITCH_MAX)
		data->player.pitch = PITCH_MAX;
	else if (data->player.pitch < PITCH_MIN)
		data->player.pitch = PITCH_MIN;
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
