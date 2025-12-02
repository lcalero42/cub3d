/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_door_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:59:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/12/02 20:20:10 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_door_grid(t_data *data);

void	init_door_system(t_data *data)
{
	int		x;
	int		y;
	char	*s;

	data->door_count = 0;
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
	init_door_grid(data);
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
		door = &data->door_grid[dy][dx];
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

static void	init_door_grid(t_data *data)
{
	int	i;
	int	y;

	data->door_grid = malloc(sizeof(t_door *) * data->grid.height);
	y = 0;
	while (y < data->grid.height)
	{
		data->door_grid[y] = malloc(sizeof(t_door) * data->grid.width);
		ft_memset(data->door_grid[y], 0, sizeof(t_door) * data->grid.width);
		y++;
	}
	i = 0;
	while (i < data->door_count)
	{
		data->door_grid[data->doors[i].y][data->doors[i].x] = data->doors[i];
		i++;
	}
}
