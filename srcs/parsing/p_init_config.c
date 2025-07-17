/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:07:10 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/16 02:56:00 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_config(t_config *config)
{
	config->path.north = NULL;
	config->path.south = NULL;
	config->path.east = NULL;
	config->path.west= NULL;
	config->floor.r = -1;
	config->floor.g = -1;
	config->floor.b = -1;
	config->ceiling.r = -1;
	config->ceiling.g = -1;
	config->ceiling.b = -1;
	config->map.grid = NULL;
	config->map.width = 0;
	config->map.height = 0;
	config->config_lines = 0;
}