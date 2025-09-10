/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_trace_shot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:08:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/10 19:59:53 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int ray_hits_enemy(t_data *data, double enemy_radius);

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
		if (data->grid.grid[map_y][map_x] == '1'
			|| data->grid.grid[map_y][map_x] == '2')
			break ;
		if (ray_hits_enemy(data, 0.3f))
		{
			data->enemy.health -= 10;
			break ;
		}
		steps++;
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

static int	ray_hits_enemy(t_data *data, double enemy_radius)
{
	double dx = data->enemy.position.x - data->player.position.x;
	double dy = data->enemy.position.y - data->player.position.y;
	double ray_dx = data->shot_ray.ray_dir.x + data->player.pitch;
	double ray_dy = data->shot_ray.ray_dir.y + data->player.pitch;
	
	double a = ray_dx * ray_dx + ray_dy * ray_dy;
	double b = 2 * (ray_dx * (-dx) + ray_dy * (-dy));
	double c = dx * dx + dy * dy - enemy_radius * enemy_radius;
	
	double discriminant = b * b - 4 * a * c;
	
	if (discriminant < 0)
		return 0;
		
	double t = (-b - sqrt(discriminant)) / (2 * a);
	return (t > 0);
}
