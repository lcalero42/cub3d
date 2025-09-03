/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:11 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/03 17:16:53 by lcalero          ###   ########.fr       */
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
	if (data->grid.grid[i][j] == '2')
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
