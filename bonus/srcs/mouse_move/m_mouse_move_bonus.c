/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mouse_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:14:46 by ekeisler          #+#    #+#             */
/*   Updated: 2025/12/04 18:12:45 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data || !data->mouse.enabled)
		return (0);
	data->mouse.center_x = WINDOW_WIDTH >> 1;
	data->mouse.center_y = WINDOW_HEIGHT >> 1;
	if (data->mouse.first_move)
		return (handle_first_move(data));
	if (check_out_of_bounds(x, y, data))
		return (0);
	data->mouse.delta_x = x - data->mouse.center_x;
	data->mouse.delta_y = y - data->mouse.center_y;
	mouse_rotation(data->mouse.delta_x, data->mouse.delta_y, data);
	return (0);
}

int	handle_first_move(t_data *data)
{
	data->mouse.first_move = 0;
	mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
		data->mouse.center_y);
	return (0);
}

int	check_out_of_bounds(int x, int y, t_data *data)
{
	int	out_of_bounds;

	out_of_bounds = (x < 10 || x > WINDOW_WIDTH - 10
			|| y < 10 || y > WINDOW_HEIGHT - 10);
	if (out_of_bounds)
	{
		mlx_mouse_move(data->mlx, data->window, data->mouse.center_x,
			data->mouse.center_y);
		return (1);
	}
	return (0);
}

void	clamp_delta(int *delta_x, int *delta_y, double magnitude)
{
	double	clamp_factor;

	if (magnitude > 200)
	{
		clamp_factor = 200.0 / magnitude;
		*delta_x = (int)(*delta_x * clamp_factor);
		*delta_y = (int)(*delta_y * clamp_factor);
	}
}
