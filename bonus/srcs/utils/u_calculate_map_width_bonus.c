/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_calculate_map_width_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:20:29 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/03 11:52:24 by ekeisler         ###   ########.fr       */
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
