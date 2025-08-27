/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_mouse_move_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:19:07 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 17:55:36 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_mouse_control(t_data *data)
{
	int	center_x;
	int	center_y;

	data->mouse.enabled = 1;
	data->mouse.first_move = 1;
	data->mouse.sensitivity = SENSITIVITY;
	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
	data->mouse.last_x = center_x;
	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, center_x, center_y);
}

void	toggle_mouse_control(t_data *data)
{
	int	center_x;
	int	center_y;

	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
	if (data->mouse.enabled)
	{
		data->mouse.enabled = 0;
		mlx_mouse_show(data->mlx, data->window);
	}
	else
	{
		data->mouse.enabled = 1;
		data->mouse.first_move = 1;
		mlx_mouse_hide(data->mlx, data->window);
		mlx_mouse_move(data->mlx, data->window, center_x, center_y);
	}
}
