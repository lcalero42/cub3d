/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check_collisions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:34:22 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 17:24:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "cub3d_bonus.h"

static int	check_point(t_data *data, double x, double y);

int	check_collisions(t_data *data, t_vector move)
{
	t_vector	new_pos;
	double		buffer;

	buffer = 0.2;
	new_pos.x = data->player.position.x + move.x;
	new_pos.y = data->player.position.y + move.y;
	if (check_point(data, new_pos.x - buffer, new_pos.y - buffer))
		return (1);
	if (check_point(data, new_pos.x + buffer, new_pos.y - buffer))
		return (1);
	if (check_point(data, new_pos.x - buffer, new_pos.y + buffer))
		return (1);
	if (check_point(data, new_pos.x + buffer, new_pos.y + buffer))
		return (1);
	return (0);
}

static int	check_point(t_data *data, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_y < 0)
		return (1);
	if (!data->grid.grid[grid_y] || !data->grid.grid[grid_y][grid_x])
		return (1);
	if (data->grid.grid[grid_y][grid_x] == '1')
		return (1);
	return (0);
}
