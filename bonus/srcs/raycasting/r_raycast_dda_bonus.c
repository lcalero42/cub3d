/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raycast_dda_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:13:02 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/14 12:44:01 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	trace_single_ray(t_data *data, int i);

void	trace_ray(t_data *data, double angle)
{
	int	i;

	init_player_direction(data, angle);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		trace_single_ray(data, i);
		i++;
	}
}

t_wall_side	get_wall_side(t_data *data, int ray_index)
{
	t_ray	*ray;

	ray = &data->rays[ray_index];
	if (ray->side == 0)
	{
		if (ray->ray_dir.x > 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->ray_dir.y > 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

void	perform_dda_step(t_data *data, int i)
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
}

static void	trace_single_ray(t_data *data, int i)
{
	init_ray_direction(data, i);
	init_ray_distances(data, i);
	init_ray_steps(data, i);
	data->rays[i].index_hit = 0;
	perform_dda(data, i);
}
