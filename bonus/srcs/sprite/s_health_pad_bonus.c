/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_health_pad_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:56:24 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/16 15:58:49 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    		render_health_sprite(t_data *data)
{
	t_sprite_bounds	bounds;
	int				health_width;
	int				health_height;

	(void)data;
	health_width = WINDOW_WIDTH;
	health_height = WINDOW_HEIGHT;
	bounds.start_x = (WINDOW_WIDTH - health_width) / 2;
	bounds.end_x = bounds.start_x + health_width - 1;
	bounds.sprite_top = WINDOW_HEIGHT - health_height;
	bounds.sprite_height = health_height;
	bounds.half_width = health_width / 2;
	bounds.sprite_size = 64;
}

void			allocate_health_pad_grid(t_data *data)
{
	int	i;
	int	y;
	
	data->health_pad_grid = malloc(sizeof(t_health_pad *) * data->grid.height);
	y = 0;
	while (y < data->grid.height)
	{
		data->health_pad_grid[y] = malloc(sizeof(t_health_pad *) * data->grid.width);
		ft_memset(data->health_pad_grid[y], 0, sizeof(t_health_pad *) * data->grid.width);
		y++;
	}
	i = 0;
	while (i < data->health_count)
	{
		data->health_pad_grid[data->health_pad[i].pos.y][data->health_pad[i].pos.x] = data->health_pad[i];
		i++;
	}
}

void			init_health_pad_system(t_data *data)
{
	int		x;
	int		y;
	char	*s;

	y = 0;
	while (y < data->grid.height)
	{
		x = 0;
		s = ft_strtrim(data->grid.grid[y], " ");
		while (s[x])
		{
			if (data->grid.grid[y][x] == 'H')
			{
				data->health_pad[data->health_count].pos.x = x;
				data->health_pad[data->health_count].pos.y = y;
				data->health_pad[data->health_count].state = 1;
				data->health_count++;
				printf("id[%d]\n", data->health_count);
				printf("x = %d\ny = %d\n", data->health_pad[data->health_count].pos.x,
					data->health_pad[data->health_count].pos.y);
			}
			x++;
		}
		free(s);
		y++;
	}
}

t_health_pad	*find_health_at(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->health_count)
	{
		if (data->health_pad[i].pos.x == x && data->health_pad[i].pos.y == y)
			return (&data->health_pad[i]);
		i++;
	}
	return (NULL);
}

// void	get_heal_pad_pos(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (data->grid.grid[i++])
// 	{
// 		j = 0;
// 		while (data->grid.grid[i][j++])
// 		{
// 			if (data->grid.grid[i][j] == 'H')
// 			{
// 				data->health_pad[i][j] =  
// 			}	
// 		}
// 	}
	
// }
