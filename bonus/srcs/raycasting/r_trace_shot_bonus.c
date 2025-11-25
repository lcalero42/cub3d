/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_trace_shot_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:08:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/25 16:04:32 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	trace_single_ray(t_data *data);
static void	perform_dda_shot(t_data *data);
static void	perform_dda_step_shot(t_data *data);

void	trace_shot(t_data *data)
{
	trace_single_ray(data);
}

static void	trace_single_ray(t_data *data)
{
	init_ray_direction_shot(data);
	init_ray_distances_shot(data);
	init_ray_steps_shot(data);
	perform_dda_shot(data);
}

static void	perform_dda_shot(t_data *data)
{
	int	steps;
	int	map_x;
	int	map_y;

	steps = 0;
	while (data->shot_ray.hit[data->shot_ray.index_hit] != 1)
	{
		perform_dda_step_shot(data);
		map_x = (int)data->shot_ray.map_pos.x;
		map_y = (int)data->shot_ray.map_pos.y;
		if (data->grid.grid[map_y][map_x] == '1'
			|| data->grid.grid[map_y][map_x] == '2')
			break ;
		if (ray_hits_enemy(data))
		{
			data->enemy.current_health -= 10;
			break ;
		}
		steps++;
	}
}

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
