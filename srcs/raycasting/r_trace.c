/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_trace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:21:48 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/08 20:56:31 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	trace_ray(t_data *data, double angle)
{
	int		i;
	double	camera_x;

	data->grid.grid = (char *[])
	{
		"111111",
		"100001",
		"102001",
		"100001",
		"111111",
		NULL
	};
	data->player.dir.x = cos(angle);
	data->player.dir.y = sin(angle);
	data->player.camera_segment.x = -sin(angle) * FOV;
	data->player.camera_segment.y = cos(angle) * FOV;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		// Initialize the ray
		ft_bzero(&data->rays[i], sizeof(t_ray));

		camera_x = 2.0 * i / (double)WINDOW_WIDTH - 1.0;
		data->rays[i].ray_dir.x = data->player.dir.x + data->player.camera_segment.x * camera_x;
		data->rays[i].ray_dir.y = data->player.dir.y + data->player.camera_segment.y * camera_x;

		// Calculate delta distances with epsilon to prevent division by zero
		data->rays[i].delta_dist.x = fabs(1.0 / (data->rays[i].ray_dir.x + 1e-30));
		data->rays[i].delta_dist.y = fabs(1.0 / (data->rays[i].ray_dir.y + 1e-30));

		data->rays[i].map_pos.x = (int)data->player.position.x;
		data->rays[i].map_pos.y = (int)data->player.position.y;

		if (data->rays[i].ray_dir.x < 0)
		{
			data->rays[i].step.x = -1;
			data->rays[i].side_dist.x = (data->player.position.x - data->rays[i].map_pos.x) * data->rays[i].delta_dist.x;
		}
		else
		{
			data->rays[i].step.x = 1;
			data->rays[i].side_dist.x = (data->rays[i].map_pos.x + 1.0 - data->player.position.x) * data->rays[i].delta_dist.x;
		}

		if (data->rays[i].ray_dir.y < 0)
		{
			data->rays[i].step.y = -1;
			data->rays[i].side_dist.y = (data->player.position.y - data->rays[i].map_pos.y) * data->rays[i].delta_dist.y;
		}
		else
		{
			data->rays[i].step.y = 1;
			data->rays[i].side_dist.y = (data->rays[i].map_pos.y + 1.0 - data->player.position.y) * data->rays[i].delta_dist.y;
		}

		while (data->rays[i].hit == 0)
		{
			if (data->rays[i].side_dist.x < data->rays[i].side_dist.y)
			{
				data->rays[i].side_dist.x += data->rays[i].delta_dist.x;
				data->rays[i].map_pos.x += data->rays[i].step.x;
				data->rays[i].side = 0;
			}
			else
			{
				data->rays[i].side_dist.y += data->rays[i].delta_dist.y;
				data->rays[i].map_pos.y += data->rays[i].step.y;
				data->rays[i].side = 1;
			}
			if (data->grid.grid[(int)data->rays[i].map_pos.y][(int)data->rays[i].map_pos.x] == '1')
				data->rays[i].hit = 1;
		}
		i++;
	}
}
