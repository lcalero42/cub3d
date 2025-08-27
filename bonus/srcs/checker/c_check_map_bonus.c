/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:16:06 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 16:26:25 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_mfw(int i, int j, t_data *data);

int	check_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->grid.grid[i])
	{
		j = 0;
		while (data->grid.grid[i][j])
		{
			if (!is_mfw(i, j, data))
				return (1);
			j++;
		}
		i++;
	}
	if (!is_map_surrounded(data))
		return (1);
	return (0);
}

static int	is_mfw(int i, int j, t_data *data)
{
	if (data->grid.grid[i][j] == '0')
		return (1);
	if (data->grid.grid[i][j] == '1')
		return (1);
	if (data->grid.grid[i][j] == 'N')
		return (1);
	if (data->grid.grid[i][j] == 'S')
		return (1);
	if (data->grid.grid[i][j] == 'W')
		return (1);
	if (data->grid.grid[i][j] == 'E')
		return (1);
	if (data->grid.grid[i][j] == ' ')
		return (1);
	else
	{
		u_print_error("Map not filled well");
		printf("found : '%c'\nx : %d\ny : %d\n",
			data->grid.grid[i][j], i + 1, j + 1);
	}
	return (0);
}
