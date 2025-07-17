/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_calculate_map_width.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:11:47 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/16 02:12:22 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void u_calculate_map_width(t_config *config)
{
    int i = 0;
    int max_width = 0;
    
    while (config->map.grid[i])
    {
        int len = ft_strlen(config->map.grid[i]);
        if (len > max_width)
            max_width = len;
        i++;
    }
    
    config->map.width = max_width;
}