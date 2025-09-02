/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raycast_init_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:19:23 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 18:19:25 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_player_direction(t_data *data, double angle)
{
	data->player.dir.x = cos(angle);
	data->player.dir.y = sin(angle);
	data->player.camera_segment.x = -sin(angle) * CAMERA_PLANE_LENGTH;
	data->player.camera_segment.y = cos(angle) * CAMERA_PLANE_LENGTH;
}

void	init_ray_direction(t_data *data, int i)
{
	double	camera_x;

	ft_bzero(&data->rays[i], sizeof(t_ray));
	data->rays[i].must_render = 1;
	camera_x = 2.0 * i / (double)WINDOW_WIDTH - 1.0;
	data->rays[i].ray_dir.x = data->player.dir.x
		+ data->player.camera_segment.x * camera_x;
	data->rays[i].ray_dir.y = data->player.dir.y
		+ data->player.camera_segment.y * camera_x;
}

void	init_ray_distances(t_data *data, int i)
{
	data->rays[i].delta_dist.x = fabs(1.0 / (data->rays[i].ray_dir.x + 1e-30));
	data->rays[i].delta_dist.y = fabs(1.0 / (data->rays[i].ray_dir.y + 1e-30));
	data->rays[i].map_pos.x = (int)data->player.position.x;
	data->rays[i].map_pos.y = (int)data->player.position.y;
}

void	init_ray_steps(t_data *data, int i)
{
	if (data->rays[i].ray_dir.x < 0)
	{
		data->rays[i].step.x = -1;
		data->rays[i].side_dist.x = (data->player.position.x
				- data->rays[i].map_pos.x) * data->rays[i].delta_dist.x;
	}
	else
	{
		data->rays[i].step.x = 1;
		data->rays[i].side_dist.x = (data->rays[i].map_pos.x + 1.0
				- data->player.position.x) * data->rays[i].delta_dist.x;
	}
	if (data->rays[i].ray_dir.y < 0)
	{
		data->rays[i].step.y = -1;
		data->rays[i].side_dist.y = (data->player.position.y
				- data->rays[i].map_pos.y) * data->rays[i].delta_dist.y;
	}
	else
	{
		data->rays[i].step.y = 1;
		data->rays[i].side_dist.y = (data->rays[i].map_pos.y + 1.0
				- data->player.position.y) * data->rays[i].delta_dist.y;
	}
}
