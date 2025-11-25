/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_init_hpad_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:55:45 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/21 04:58:02 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	add_health_pad_at_pos(t_data *data, int x, int y);
static int	process_row(t_data *data, int y);

void	init_health_pad_system(t_data *data)
{
	int	y;

	data->health_count = 0;
	y = 0;
	while (y < data->grid.height)
	{
		if (!process_row(data, y))
			close_window(data);
		y++;
	}
}

static int	add_health_pad_at_pos(t_data *data, int x, int y)
{
	if (data->health_count >= MAX_HEALTH_PAD)
	{
		u_print_error("HEALTH PAD > 64");
		return (0);
	}
	data->health_pad[data->health_count].pos.x = x;
	data->health_pad[data->health_count].pos.y = y;
	data->health_pad[data->health_count].state = 1;
	data->health_pad[data->health_count].distance = 0;
	data->health_count++;
	return (1);
}

static int	process_row(t_data *data, int y)
{
	int	x;

	x = 0;
	while (x < data->grid.width && data->grid.grid[y][x])
	{
		if (data->grid.grid[y][x] == 'H')
		{
			if (!add_health_pad_at_pos(data, x, y))
				return (0);
		}
		x++;
	}
	return (1);
}
