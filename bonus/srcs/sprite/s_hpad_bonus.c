/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_hpad_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:11:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/20 20:00:48 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_health_pad_system(t_data *data)
{
	int	x;
	int	y;

	data->health_count = 0;
	y = 0;
	while (y < data->grid.height)
	{
		x = 0;
		while (x < data->grid.width && data->grid.grid[y][x])
		{
			if (data->grid.grid[y][x] == 'H')
			{
				data->health_pad[data->health_count].pos.x = x;
				data->health_pad[data->health_count].pos.y = y;
				data->health_pad[data->health_count].state = 1;
				data->health_pad[data->health_count].distance = 0;
				data->health_count++;
			}
			x++;
		}
		y++;
	}
}

static void	pickup_health(t_data *data, int i)
{
	data->player.current_health += 25.0;
	if (data->player.current_health > data->player.max_health)
		data->player.current_health = data->player.max_health;
	data->health_pad[i].state = 0;
	data->grid.grid[(int)data->health_pad[i].pos.y]
	[(int)data->health_pad[i].pos.x] = '0';
}

void	check_health_pickup_collision(t_data *data)
{
	int		i;
	double	dx;
	double	dy;
	double	distance;

	i = 0;
	while (i < data->health_count)
	{
		if (data->health_pad[i].state == 1)
		{
			dx = data->player.position.x - (data->health_pad[i].pos.x + 0.5);
			dy = data->player.position.y - (data->health_pad[i].pos.y + 0.5);
			distance = sqrt(dx * dx + dy * dy);
			if (distance < 0.5)
				pickup_health(data, i);
		}
		i++;
	}
}
