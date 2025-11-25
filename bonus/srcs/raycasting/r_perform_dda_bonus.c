/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_perform_dda_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:04:11 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/16 15:02:47 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	store_hit(t_data *data, int i, t_pos map_pos, int hit_type)
{
	int	idx;

	idx = data->rays[i].index_hit;
	data->rays[i].hit[idx] = hit_type;
	data->rays[i].hit_map_pos[idx].x = map_pos.x;
	data->rays[i].hit_map_pos[idx].y = map_pos.y;
	data->rays[i].side_per_hit[idx] = data->rays[i].side;
	if (data->rays[i].side == 0)
		data->rays[i].perp_wall_dist_per_hit[idx]
			= (data->rays[i].map_pos.x - data->player.position.x
				+ (1 - data->rays[i].step.x) / 2) / data->rays[i].ray_dir.x;
	else
		data->rays[i].perp_wall_dist_per_hit[idx]
			= (data->rays[i].map_pos.y - data->player.position.y
				+ (1 - data->rays[i].step.y) / 2) / data->rays[i].ray_dir.y;
	data->rays[i].index_hit++;
}

static int	handle_hit(t_data *data, int i, t_pos map_pos)
{
	t_door	*door;
	char	cell;

	if (map_pos.x < 0 || map_pos.x >= data->grid.width
		|| map_pos.y < 0 || map_pos.y >= data->grid.height)
		return (1);
	cell = data->grid.grid[map_pos.y][map_pos.x];
	if (cell == '1')
	{
		store_hit(data, i, map_pos, 1);
		return (1);
	}
	else if (cell == '2')
	{
		door = &data->door_grid[map_pos.y][map_pos.x];
		if (door)
		{
			store_hit(data, i, map_pos, 2);
			if (door->state == DOOR_CLOSED)
				return (1);
		}
	}
	return (0);
}

void	perform_dda(t_data *data, int i)
{
	int		steps;
	t_pos	map_pos;
	t_ray	*ray;

	ray = &data->rays[i];
	steps = 1;
	while (1)
	{
		perform_dda_step(data, i);
		map_pos.x = (int)ray->map_pos.x;
		map_pos.y = (int)ray->map_pos.y;
		if (handle_hit(data, i, map_pos))
			break ;
		steps++;
		if (steps > RENDER_DISTANCE)
		{
			ray->must_render = 0;
			break ;
		}
	}
}
