/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_find_player_pos_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:50 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/03 11:51:12 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	set_player_angle(int i, int j, t_data *data);
static int	player_is_found(int i, int j, t_data *data);
static int	check_player_num(int found);

int	find_player_pos(t_data *data)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (data->grid.grid[i])
	{
		j = 0;
		while (data->grid.grid[i][j])
		{
			if (!player_is_found(i, j, data))
			{
				data->player.position.x = j + 0.5;
				data->player.position.y = i + 0.5;
				set_player_angle(i, j, data);
				found += 1;
			}
			j++;
		}
		i++;
	}
	if (check_player_num(found))
		return (1);
	return (0);
}

static int	check_player_num(int found)
{
	if (found == 0 || found > 1)
	{
		if (found == 0)
			u_print_error("No player position found in the map");
		else
			u_print_error("More than one player position found in the map");
		return (1);
	}
	return (0);
}

static int	player_is_found(int i, int j, t_data *data)
{
	if (data->grid.grid[i][j] == 'N'
	|| data->grid.grid[i][j] == 'S'
	|| data->grid.grid[i][j] == 'W'
	|| data->grid.grid[i][j] == 'E')
		return (0);
	return (1);
}

static int	set_player_angle(int i, int j, t_data *data)
{
	if (data->grid.grid[i][j] == 'N')
		data->player.angle = -1.575;
	if (data->grid.grid[i][j] == 'S')
		data->player.angle = 1.575;
	if (data->grid.grid[i][j] == 'W')
		data->player.angle = 3.15;
	if (data->grid.grid[i][j] == 'E')
		data->player.angle = 0;
	return (0);
}
