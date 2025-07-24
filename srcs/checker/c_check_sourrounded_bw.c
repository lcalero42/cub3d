/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_sourrounded_bw.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:47:10 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/24 15:58:23 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable_space(char c);
static int	has_open_neighbor(char **map, int x, int y, int height, int width);
static int	check_neighbor(char **map, int nx, int ny, int height, int width);
static int	is_out_of_bounds(int x, int y, int height, int width);
static int	is_valid_map_char(char c);

int	is_map_surrounded(char **map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (is_walkable_space(map[i][j]))
			{
				if (has_open_neighbor(map, i, j, height, width))
					return (0);
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

static int	has_open_neighbor(char **map, int x, int y, int height, int width)
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
		if (check_neighbor(map, nx, ny, height, width))
			return (1);
		i++;
	}
	return (0);
}

static int	check_neighbor(char **map, int nx, int ny, int height, int width)
{
	if (is_out_of_bounds(nx, ny, height, width))
		return (1);
	if (map[nx][ny] == ' ' || map[nx][ny] == '\0')
		return (1);
	if (!is_valid_map_char(map[nx][ny]))
		return (1);
	return (0);
}

static int	is_out_of_bounds(int x, int y, int height, int width)
{
	return (x < 0 || x >= height || y < 0 || y >= width);
}

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
