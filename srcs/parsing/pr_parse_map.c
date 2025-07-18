/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:59:55 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/18 02:18:41 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map(char **all_lines, t_data *data)
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
	data->grid.grid = malloc(sizeof(char *) * (map_line_count + 1));
	if (!data->grid.grid)
		return (0);
	i = map_start;
	map_idx = 0;
	while (all_lines[i] && map_idx < map_line_count)
	{
		if(!u_is_empty_line(all_lines[i]))
		{
			data->grid.grid[map_idx] = ft_strdup(all_lines[i]);
			if (!data->grid.grid[map_idx])
				return (0);
			map_idx++;
		}
		i++;
	}
	data->grid.grid[map_idx] = NULL;
	data->grid.height = map_line_count;
	u_calculate_map_width(data);
	return (1);	
}
