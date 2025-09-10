/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_trace_shot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:28:17 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/10 17:31:27 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_ray_direction_shot(t_data *data)
{
	double	camera_x;

	ft_bzero(&data->shot_ray, sizeof(t_ray));
	data->shot_ray.must_render = 1;
	camera_x = 2.0 * (WINDOW_WIDTH / 2) / (double)WINDOW_WIDTH - 1.0;
	data->shot_ray.ray_dir.x = data->player.dir.x
		+ data->player.camera_segment.x * camera_x;
	data->shot_ray.ray_dir.y = data->player.dir.y
		+ data->player.camera_segment.y * camera_x;
}

void	init_ray_distances_shot(t_data *data)
{
	data->shot_ray.delta_dist.x = fabs(1.0 / (data->shot_ray.ray_dir.x
				+ 1e-30));
	data->shot_ray.delta_dist.y = fabs(1.0 / (data->shot_ray.ray_dir.y
				+ 1e-30));
	data->shot_ray.map_pos.x = (int)data->player.position.x;
	data->shot_ray.map_pos.y = (int)data->player.position.y;
}

void	init_ray_steps_shot(t_data *data)
{
	if (data->shot_ray.ray_dir.x < 0)
	{
		data->shot_ray.step.x = -1;
		data->shot_ray.side_dist.x = (data->player.position.x
				- data->shot_ray.map_pos.x) * data->shot_ray.delta_dist.x;
	}
	else
	{
		data->shot_ray.step.x = 1;
		data->shot_ray.side_dist.x = (data->shot_ray.map_pos.x + 1.0
				- data->player.position.x) * data->shot_ray.delta_dist.x;
	}
	if (data->shot_ray.ray_dir.y < 0)
	{
		data->shot_ray.step.y = -1;
		data->shot_ray.side_dist.y = (data->player.position.y
				- data->shot_ray.map_pos.y) * data->shot_ray.delta_dist.y;
	}
	else
	{
		data->shot_ray.step.y = 1;
		data->shot_ray.side_dist.y = (data->shot_ray.map_pos.y + 1.0
				- data->player.position.y) * data->shot_ray.delta_dist.y;
	}
}
