/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_calculate_map_width.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:11:47 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/18 02:16:22 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void u_calculate_map_width(t_data *data)
{
    int i = 0;
    int max_width = 0;
    
    while (data->grid.grid[i])
    {
        int len = ft_strlen(data->grid.grid[i]);
        if (len > max_width)
            max_width = len;
        i++;
    }
    data->grid.width = max_width;
}