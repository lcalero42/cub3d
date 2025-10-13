/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_door_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:59:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/13 13:29:25 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_door_system(t_data *data)
{
	int		x;
	int		y;
	char	*s;

	y = 0;
	while (y < data->grid.height && data->door_count < MAX_DOORS)
	{
		x = 0;
		s = ft_strtrim(data->grid.grid[y], " ");
		while (s[x] && data->door_count < MAX_DOORS)
		{
			if (data->grid.grid[y][x] == '2')
			{
				data->doors[data->door_count].x = x;
				data->doors[data->door_count].y = y;
				data->doors[data->door_count].state = DOOR_CLOSED;
				data->door_count++;
			}
			x++;
		}
		free(s);
		y++;
	}
}

t_door	*find_door_at(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

void	check_door_interaction(t_data *data, int keycode)
{
	t_door		*door;
	long long	current_time;
	int			dx;
	int			dy;
	double		dist;

	if (keycode != XK_space)
		return ;
	current_time = get_current_time();
	dx = (int)(data->player.position.x + cos(data->player.angle));
	dy = (int)(data->player.position.y + sin(data->player.angle));
	dist = sqrt((data->player.position.x - (dx + 0.5))
			* (data->player.position.x - (dx + 0.5))
			+ (data->player.position.y - (dy + 0.5))
			* (data->player.position.y - (dy + 0.5)));
	if (data->grid.grid[dy][dx] == '2')
	{
		door = find_door_at(data, dx, dy);
		if (door && dist > 0.7f)
		{
			toggle_door(door);
			data->last_door_interaction = current_time;
		}
	}
}

void	toggle_door(t_door *door)
{
	if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPEN;
	else
		door->state = DOOR_CLOSED;
}

t_texture_info	get_door_texture(t_data *data, t_door *door)
{
	if (door->state == DOOR_CLOSED)
		return (data->door_closed.info);
	else
		return (data->door_opened.info);
}
