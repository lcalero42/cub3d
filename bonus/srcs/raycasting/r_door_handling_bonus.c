/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_door_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:59:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/09 15:38:55 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_door_system(t_data *data)
{
	int		x;
	int		y;
	int		door_index;
	char	*line;

	door_index = 0;
	data->door_count = 0;
	y = 0;
	while (y < data->grid.height && door_index < MAX_DOORS)
	{
		x = 0;
		line = ft_strtrim(data->grid.grid[y], " ");
		while (x < (int)ft_strlen(line) && door_index < MAX_DOORS)
		{
			if (data->grid.grid[y][x] == '2')
			{
				data->doors[door_index].x = x;
				data->doors[door_index].y = y;
				data->doors[door_index].state = DOOR_CLOSED;
				data->doors[door_index].last_interaction_time = 0;
				door_index++;
			}
		}
		free(line);
		y++;
	}
	data->door_count = door_index;
	data->last_door_interaction = 0;
}

t_door	*find_door_at(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		if ((data->doors[i].x == x) && (data->doors[i].y == y))
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

void	check_door_interaction(t_data *data, int keycode)
{
	t_ray		middle_ray;
	int			map_x;
	int			map_y;
	t_door		*door;
	long long	current_time;

	if (keycode != XK_space)
		return ;
	current_time = get_current_time();
	middle_ray = data->rays[WINDOW_WIDTH / 2];
	map_x = (int)middle_ray.map_pos.x;
	map_y = (int)middle_ray.map_pos.y;
	if (data->grid.grid[(int)(data->player.position.y
			+ sin(data->player.angle))]
			[(int)(data->player.position.x + cos(data->player.angle))] == '2')
	{
		door = find_door_at(data, (int)(data->player.position.x
					+ cos(data->player.angle)),
				(int)(data->player.position.y + sin(data->player.angle)));
		if (door)
		{
			if (current_time - door->last_interaction_time < 500)
				return ;
			toggle_door(door);
			door->last_interaction_time = current_time;
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

int	should_door_block_ray(t_door *door)
{
	return (door->state == DOOR_CLOSED);
}
