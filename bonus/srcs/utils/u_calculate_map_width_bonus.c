/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_calculate_map_width_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/02 17:27:41 by lcalero          ###   ########.fr       */
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
