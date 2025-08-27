/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mouse_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:14:46 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 17:55:41 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	apply_rotation(t_data *data, int center_x, int center_y, int x);

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;
	int		center_x;
	int		center_y;

	data = (t_data *)param;
	(void)y;
	if (!data || !data->mouse.enabled)
		return (0);
	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
	if (data->mouse.first_move)
	{
		data->mouse.last_x = center_x;
		data->mouse.first_move = 0;
		mlx_mouse_move(data->mlx, data->window, center_x, center_y);
		return (0);
	}
	apply_rotation(data, center_x, center_y, x);
	return (0);
}

static void	apply_rotation(t_data *data, int center_x, int center_y, int x)
{
	int		delta_x;
	double	rotation_amount;

	delta_x = x - center_x;
	rotation_amount = delta_x * data->mouse.sensitivity * 0.001f;
	data->player.angle += rotation_amount;
	while (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	while (data->player.angle >= 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	data->player.camera_segment.x = -data->player.dir.y * CAMERA_PLANE_LENGTH;
	data->player.camera_segment.y = data->player.dir.x * CAMERA_PLANE_LENGTH;
	mlx_mouse_move(data->mlx, data->window, center_x, center_y);
	data->mouse.last_x = center_x;
}
