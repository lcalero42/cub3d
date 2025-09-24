/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_door_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:59:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/24 17:22:18 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_door_system(t_data *data)
{
	int	x;
	int	y;
	int	door_index;

	door_index = 0;
	data->door_count = 0;
	y = 0;
	while (y < data->grid.height && door_index < MAX_DOORS)
	{
		x = 0;
		while (x < data->grid.width && door_index < MAX_DOORS)
		{
			if (data->grid.grid[y][x] == '2')
			{
				data->doors[door_index].x = x;
				data->doors[door_index].y = y;
				data->doors[door_index].state = DOOR_CLOSED;
				data->doors[door_index].open_progress = 0.0;
				data->doors[door_index].last_interaction_time = 0;
				door_index++;
			}
			x++;
		}
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
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

void	update_doors(t_data *data)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < data->door_count)
	{
		door = &data->doors[i];
		if (door->state == DOOR_OPENING)
		{
			door->open_progress += DOOR_ANIMATION_SPEED;
			if (door->open_progress >= 1.0)
			{
				door->open_progress = 1.0;
				door->state = DOOR_OPEN;
			}
		}
		else if (door->state == DOOR_CLOSING)
		{
			door->open_progress -= DOOR_ANIMATION_SPEED;
			if (door->open_progress <= 0.0)
			{
				door->open_progress = 0.0;
				door->state = DOOR_CLOSED;
			}
		}
		i++;
	}
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
	// if (current_time - data->last_door_interaction < DOOR_INTERACTION_COOLDOWN)
	// 	return ;
	middle_ray = data->rays[WINDOW_WIDTH / 2];
	map_x = (int)middle_ray.map_pos.x;
	map_y = (int)middle_ray.map_pos.y;
	int dx = (int)(data->player.position.x + cos(data->player.angle));
	int dy = (int)(data->player.position.y + sin(data->player.angle));
	if (data->grid.grid[dy][dx] == '2')
	{
		door = find_door_at(data, dx, dy);
		if (door)
		{
			toggle_door(door);
			data->last_door_interaction = current_time;
		}
	}
}

void	toggle_door(t_door *door)
{
	if (door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
		door->state = DOOR_OPENING;
	else if (door->state == DOOR_OPEN || door->state == DOOR_OPENING)
		door->state = DOOR_CLOSING;
}

t_texture_info	get_door_texture(t_data *data, t_door *door)
{
	if (door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
		return (data->door_closed.info);
	else
		return (data->door_opened.info);
}

int	should_door_block_ray(t_door *door, t_ray *ray)
{
	double	ray_offset;
	double	door_opening;

	if (door->open_progress <= 0.1)
		return (1);
	if (door->open_progress >= 0.9)
		return (0);
	if (ray->side == 0)
		ray_offset = ray->map_pos.y - floor(ray->map_pos.y);
	else
		ray_offset = ray->map_pos.x - floor(ray->map_pos.x);
	door_opening = door->open_progress;
	if (ray_offset < door_opening)
		return (0);
	return (1);
}
