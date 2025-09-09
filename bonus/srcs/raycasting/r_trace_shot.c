/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_trace_shot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:08:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/09 20:28:44 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	perform_dda_step_shot(t_data *data)
{
	if (data->shot_ray.side_dist.x < data->shot_ray.side_dist.y)
	{
		data->shot_ray.side_dist.x += data->shot_ray.delta_dist.x;
		data->shot_ray.map_pos.x += data->shot_ray.step.x;
		data->shot_ray.side = 0;
	}
	else
	{
		data->shot_ray.side_dist.y += data->shot_ray.delta_dist.y;
		data->shot_ray.map_pos.y += data->shot_ray.step.y;
		data->shot_ray.side = 1;
	}
}

static void	perform_dda_shot(t_data *data)
{
	int	steps;
	int	map_x;
	int	map_y;

	steps = 0;
	while (data->shot_ray.hit == 0)
	{
		perform_dda_step_shot(data);
		map_x = (int)data->shot_ray.map_pos.x;
		map_y = (int)data->shot_ray.map_pos.y;
		if (map_x == (int)data->enemy.position.x
			&& map_y == (int)data->enemy.position.y)
		{
			data->enemy.health -= 10;
			break ;
		}
		steps++;
		if (steps > RENDER_DISTANCE)
		{
			data->shot_ray.hit = 1;
			data->shot_ray.must_render = 0;
			break ;
		}
	}
}

static void	trace_single_ray(t_data *data)
{
	init_ray_direction_shot(data);
	init_ray_distances_shot(data);
	init_ray_steps_shot(data);
	perform_dda_shot(data);
}

void	trace_shot(t_data *data)
{
	trace_single_ray(data);
}
