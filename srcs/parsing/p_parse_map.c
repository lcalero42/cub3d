/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:59:55 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/16 02:57:05 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map(char **all_lines, t_config *config)
{
	int	i;
	int	map_start;
	int	map_line_count;
	int	map_idx;
	
	i = 0;
	map_start = 0;
	map_line_count = 0;
	while (all_lines[i])
	{
		if	(u_is_empty_line(all_lines[i]) || u_is_config_line(all_lines[i]))
		{
			i++;
			continue ;
		}
		else
		{
			map_start = i;
			break ;
		}
	}
	i = map_start;
	while (all_lines[i])
	{
		if (!u_is_config_line(all_lines[i]) && !u_is_empty_line(all_lines[i]))
			map_line_count++;
		i++;
	}
	if (map_line_count == 0)
	{
		printf("error: no map found\n");
		return (0);
	}
	config->map.grid = malloc(sizeof(char *) * (map_line_count + 1));
	if (!config->map.grid)
		return (0);
	i = map_start;
	map_idx = 0;
	while (all_lines[i] && map_idx < map_line_count)
	{
		if(!u_is_empty_line(all_lines[i]))
		{
			config->map.grid[map_idx] = ft_strdup(all_lines[i]);
			if (!config->map.grid[map_idx])
				return (0);
			map_idx++;
		}
		i++;
	}
	config->map.grid[map_idx] = NULL;
	config->map.height = map_line_count;
	u_calculate_map_width(config);
	return (1);	
}
