/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_calculate_map_width_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:11:47 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 17:57:17 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	u_calculate_map_width(t_data *data)
{
	int	i;
	int	max_width;
	int	len;

	i = 0;
	max_width = 0;
	len = 0;
	while (data->grid.grid[i])
	{
		len = ft_strlen(data->grid.grid[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	data->grid.width = max_width;
}
