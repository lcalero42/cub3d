/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_door_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:59:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/04 18:13:32 by lcalero          ###   ########.fr       */
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
		data->grid.grid[map_y][map_x] = '3';
	else if (middle_ray.hit == 3 && data->rays[WINDOW_WIDTH
			/ 2].perp_wall_dist < 1.0f && keycode == XK_space)
		data->grid.grid[map_y][map_x] = '2';
}

void	print_door_mess(t_data *data)
{
	int		map_x;
	int		map_y;
	t_ray	middle_ray;

	middle_ray = data->rays[WINDOW_WIDTH / 2];
	map_x = (int)middle_ray.map_pos.x;
	map_y = (int)middle_ray.map_pos.y;
	if (middle_ray.hit == 2 && data->rays[WINDOW_WIDTH
			/ 2].perp_wall_dist < 1.0f)
		mlx_string_put(data->mlx, data->window, WINDOW_WIDTH * 0.45,
			WINDOW_HEIGHT * 0.4, 0xFFFFFF, "Press space to open the door");
	else if (middle_ray.hit == 3 && data->rays[WINDOW_WIDTH
			/ 2].perp_wall_dist < 1.0f)
		mlx_string_put(data->mlx, data->window, WINDOW_WIDTH * 0.45,
			WINDOW_HEIGHT * 0.4, 0xFFFFFF, "Press space to close the door");
}
