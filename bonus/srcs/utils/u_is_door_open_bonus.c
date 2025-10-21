/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_is_door_open_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:35:05 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/21 02:29:42 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_door_open(t_data *data, int x, int i)
{
	t_pos	door_pos;
	t_door	*door;

	door_pos = data->rays[x].hit_map_pos[i];
	if (door_pos.y < 0 || door_pos.y >= data->grid.height
		|| door_pos.x < 0 || door_pos.x >= data->grid.width)
		return (0);
	door = &data->door_grid[door_pos.y][door_pos.x];
	if (!door)
		return (0);
	if (door->state == DOOR_OPEN)
		return (1);
	return (0);
}
