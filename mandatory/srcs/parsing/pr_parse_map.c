/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:59:55 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/26 16:56:29 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_map_start(char **all_lines);
static int	count_map_lines(char **all_lines, int map_start);
static int	allocate_grid(t_data *data, int map_line_count);
static int	fill_grid(char **all_lines, t_data *data, int map_start, int count);

int	parse_map(char **all_lines, t_data *data)
{
	int	map_start;
	int	map_line_count;

	map_start = find_map_start(all_lines);
	if (map_start == -1)
	{
		u_print_error("No map found");
		return (0);
	}
	map_line_count = count_map_lines(all_lines, map_start);
	if (map_line_count == -1)
	{
		u_print_error("Map too big");
		return (0);
	}
	if (!allocate_grid(data, map_line_count))
		return (0);
	if (!fill_grid(all_lines, data, map_start, map_line_count))
		return (0);
	data->grid.height = map_line_count;
	u_calculate_map_width(data);
	return (1);
}

static int	find_map_start(char **all_lines)
{
	int	i;

	i = 0;
	while (all_lines[i])
	{
		if (!u_is_empty_line(all_lines[i]) && !u_is_config_line(all_lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	count_map_lines(char **all_lines, int map_start)
{
	int	i;
	int	count;
	int	len;

	i = map_start;
	count = 0;
	len = 0;
	while (all_lines[i])
	{
		if (!u_is_config_line(all_lines[i]) && !u_is_empty_line(all_lines[i]))
			count++;
		len = ft_strlen(all_lines[i]);
		if (len > MAX_LINE_LEN)
			return (-1);
		i++;
	}
	if (count > MAX_MAP_LINES)
		return (-1);
	return (count);
}

static int	allocate_grid(t_data *data, int map_line_count)
{
	if (map_line_count == 0)
	{
		u_print_error("No map found");
		return (0);
	}
	data->grid.grid = malloc(sizeof(char *) * (map_line_count + 1));
	if (!data->grid.grid)
		close_window(data);
	return (1);
}

static int	fill_grid(char **all_lines, t_data *data, int map_start, int count)
{
	int	i;
	int	map_idx;

	i = map_start;
	map_idx = 0;
	while (all_lines[i] && map_idx < count)
	{
		if (!u_is_empty_line(all_lines[i]))
		{
			data->grid.grid[map_idx] = ft_strdup(all_lines[i]);
			if (!data->grid.grid[map_idx])
			{
				free_grid_partial(data, map_idx);
				return (0);
			}
			map_idx++;
		}
		i++;
	}
	data->grid.grid[map_idx] = NULL;
	return (1);
}
