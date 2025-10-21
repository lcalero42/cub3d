/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_map_checking_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:14:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/21 17:44:30 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_out_of_bounds(int x, int y, int height, int width)
{
	return (x < 0 || x >= height || y < 0 || y >= width);
}

int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '2' || c == 'H');
}

int	is_valid_spawn(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->grid.height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(data->grid.grid[y]))
		return (0);
	if (data->grid.grid[y][x] != '0')
		return (0);
	return (1);
}
