/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_sourrounded_bw_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:47:10 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 16:26:20 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_walkable_space(char c);
static int	has_open_neighbor(t_data *data, int x, int y);
static int	check_neighbor(t_data *data, int nx, int ny);

int	is_map_surrounded(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->grid.grid[i])
	{
		j = 0;
		while (data->grid.grid[i][j])
		{
			if (is_walkable_space(data->grid.grid[i][j]))
			{
				if (has_open_neighbor(data, i, j))
				{
					u_print_error("Map not surrounded by walls");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_walkable_space(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	has_open_neighbor(t_data *data, int x, int y)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	nx;
	int	ny;

	dx[0] = -1;
	dx[1] = 1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = -1;
	dy[3] = 1;
	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (check_neighbor(data, nx, ny))
			return (1);
		i++;
	}
	return (0);
}

static int	check_neighbor(t_data *data, int nx, int ny)
{
	if (is_out_of_bounds(nx, ny, data->grid.height, data->grid.width))
		return (1);
	if (data->grid.grid[nx][ny] == ' ' || data->grid.grid[nx][ny] == '\0')
		return (1);
	if (!is_valid_map_char(data->grid.grid[nx][ny]))
		return (1);
	return (0);
}
