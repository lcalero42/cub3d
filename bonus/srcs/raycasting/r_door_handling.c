/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_door_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:59:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/08 16:30:45 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_door_distance(t_data *data, int keycode)
{
	int		map_x;
	int		map_y;
	t_ray	middle_ray;

	middle_ray = data->rays[WINDOW_WIDTH / 2];
	map_x = (int)middle_ray.map_pos.x;
	map_y = (int)middle_ray.map_pos.y;
	if (middle_ray.hit == 2 && data->rays[WINDOW_WIDTH
			/ 2].perp_wall_dist < 1.0f && keycode == XK_space)
		data->grid.grid[map_y][map_x] = '0';
}
