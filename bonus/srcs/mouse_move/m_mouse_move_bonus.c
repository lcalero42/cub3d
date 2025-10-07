/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mouse_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:14:46 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/07 14:47:13 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	mouse_rotation(int center_x, int center_y, t_data *data);
static void	normalize_angle(double *angle, t_data *data);

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
	int		smooth_x;
	int		smooth_y;
	double	magnitude;
	double	clamp_factor;

	magnitude = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (magnitude > 100)
	{
		mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
			data->mouse.center_y);
	}
	if (magnitude > 200)
	{
		clamp_factor = 200.0 / magnitude;
		delta_x = (int)(delta_x * clamp_factor);
		delta_y = (int)(delta_y * clamp_factor);
	}
	add_to_smooth_buffer(data, delta_x, delta_y);
	get_smoothed_delta(data, &smooth_x, &smooth_y);
	apply_rotation_with_limits(data, smooth_x, smooth_y);
	normalize_angle(&data->player.angle, data);
	update_player_direction(data);
	mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
		data->mouse.center_y);
}

static void	normalize_angle(double *angle, t_data *data)
{
	(void)data;
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}

