/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raycast_dda.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:13:02 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/17 21:55:59 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	perform_dda_step(t_data *data, int i);
static void	perform_dda(t_data *data, int i);
static void	trace_single_ray(t_data *data, int i);

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

static void	perform_dda_step(t_data *data, int i)
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

static void	perform_dda(t_data *data, int i)
{
	while (data->rays[i].hit == 0)
	{
		perform_dda_step(data, i);
		if (data->grid.grid[(int)data->rays[i].map_pos.y]
			[(int)data->rays[i].map_pos.x] == '1')
			data->rays[i].hit = 1;
	}
}

static void	trace_single_ray(t_data *data, int i)
{
	init_ray_direction(data, i);
	init_ray_distances(data, i);
	init_ray_steps(data, i);
	perform_dda(data, i);
}
