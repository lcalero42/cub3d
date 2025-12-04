/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_mouse_move_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:24 by lcalero           #+#    #+#             */
/*   Updated: 2025/12/04 18:11:32 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_mouse_move_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:24 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/08 16:51:28 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_smooth_buffer(t_data *data)
{
	int	i;

	data->mouse.m_smooth.buffer_index = 0;
	data->mouse.m_smooth.buffer_filled = 0;
	data->mouse.recenter_frame_counter = 0;
	i = 0;
	while (i < 5)
	{
		data->mouse.m_smooth.buffer_x[i] = 0;
		data->mouse.m_smooth.buffer_y[i] = 0;
		i++;
	}
}

void	init_mouse_control(t_data *data)
{
	int	center_x;
	int	center_y;

	data->mouse.enabled = 1;
	data->player.pitch = 0.0;
	data->mouse.first_move = 1;
	data->mouse.sensitivity = SENSITIVITY;
	center_x = WINDOW_WIDTH >> 1;
	center_y = WINDOW_HEIGHT >> 1;
	init_smooth_buffer(data);
	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, center_x, center_y);
}

void	toggle_mouse_control(t_data *data)
{
	int	center_x;
	int	center_y;

	center_x = WINDOW_WIDTH >> 1;
	center_y = WINDOW_HEIGHT >> 1;
	if (data->mouse.enabled)
	{
		data->mouse.enabled = 0;
		mlx_mouse_show(data->mlx, data->window);
	}
	else
	{
		data->mouse.enabled = 1;
		data->mouse.first_move = 1;
		init_smooth_buffer(data);
		mlx_mouse_hide(data->mlx, data->window);
		mlx_mouse_move(data->mlx, data->window, center_x, center_y);
	}
}
