/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_perform_dda_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:04:11 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/12 20:47:42 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	store_hit_wall(t_data *data, int i, int map_x, int map_y)
{
	data->rays[i].hit[data->rays[i].index_hit] = 1;
	data->rays[i].hit_map_pos[data->rays[i].index_hit].x = map_x;
	data->rays[i].hit_map_pos[data->rays[i].index_hit].y = map_y;
	data->rays[i].side_per_hit[data->rays[i].index_hit] = data->rays[i].side;
	if (data->rays[i].side == 0)
		data->rays[i].perp_wall_dist_per_hit[data->rays[i].index_hit]
			= (data->rays[i].map_pos.x - data->player.position.x
				+ (1 - data->rays[i].step.x) / 2) / data->rays[i].ray_dir.x;
	else
		data->rays[i].perp_wall_dist_per_hit[data->rays[i].index_hit]
			= (data->rays[i].map_pos.y - data->player.position.y
				+ (1 - data->rays[i].step.y) / 2) / data->rays[i].ray_dir.y;
	data->rays[i].index_hit++;
}

static void	store_hit_door(t_data *data, int i, int map_x, int map_y)
{
	data->rays[i].hit[data->rays[i].index_hit] = 2;
	data->rays[i].hit_map_pos[data->rays[i].index_hit].x = map_x;
	data->rays[i].hit_map_pos[data->rays[i].index_hit].y = map_y;
	data->rays[i].side_per_hit[data->rays[i].index_hit] = data->rays[i].side;
	if (data->rays[i].side == 0)
		data->rays[i].perp_wall_dist_per_hit[data->rays[i].index_hit]
			= (data->rays[i].map_pos.x - data->player.position.x
				+ (1 - data->rays[i].step.x) / 2) / data->rays[i].ray_dir.x;
	else
		data->rays[i].perp_wall_dist_per_hit[data->rays[i].index_hit]
			= (data->rays[i].map_pos.y - data->player.position.y
				+ (1 - data->rays[i].step.y) / 2) / data->rays[i].ray_dir.y;
	data->rays[i].index_hit++;
}

static int	handle_hit(t_data *data, int i, int map_x, int map_y)
{
	t_door	*door;

	if (data->grid.grid[map_y][map_x] == '1')
	{
		store_hit_wall(data, i, map_x, map_y);
		return (1);
	}
	else if (data->grid.grid[map_y][map_x] == '2')
	{
		door = find_door_at(data, map_x, map_y);
		if (door)
		{
			store_hit_door(data, i, map_x, map_y);
			if (door->state == DOOR_CLOSED)
				return (1);
		}
	}
	return (0);
}

void	perform_dda(t_data *data, int i)
{
	int	steps;
	int	map_x;
	int	map_y;

	steps = 1;
	while (1)
	{
		perform_dda_step(data, i);
		map_x = (int)data->rays[i].map_pos.x;
		map_y = (int)data->rays[i].map_pos.y;
		if (handle_hit(data, i, map_x, map_y))
			break ;
		steps++;
		if (steps > RENDER_DISTANCE)
		{
			data->rays[i].must_render = 0;
			break ;
		}
	}
}
