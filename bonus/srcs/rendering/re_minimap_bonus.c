/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:45:42 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/09 15:28:26 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_minimap_params(t_data *data, t_minimap_params *params)
{
	params->cell_size = WINDOW_WIDTH / 120;
	if (params->cell_size < 5)
		params->cell_size = 5;
	if (params->cell_size > 16)
		params->cell_size = 16;
	params->minimap_margin = WINDOW_WIDTH * 0.05;
	params->minimap_size = fmax(data->grid.width, data->grid.height)
		* params->cell_size;
	params->start_x = WINDOW_WIDTH - params->minimap_size * 1.05;
	params->start_y = params->minimap_margin;
}

static void	draw_cell_helper(t_data *data, char cell, t_square_params *square)
{
	if (cell != ' ')
	{
		square->color = 0xFFFFFF;
		draw_square(data, *square);
	}
	if (cell == '1')
	{
		square->color = 0x000000;
		draw_square(data, *square);
	}
	if (cell == '2')
	{
		square->color = 0x8B4513;
		draw_square(data, *square);
	}
}

static void	draw_minimap_cell(t_data *data, t_minimap_params *params,
	int i, int j)
{
	t_square_params	square;

	square.x = params->start_x + j * params->cell_size;
	square.y = params->start_y + i * params->cell_size;
	square.scale = params->cell_size;
	draw_cell_helper(data, data->grid.grid[i][j], &square);
}

static void	draw_minimap_grid(t_data *data, t_minimap_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (data->grid.grid[i])
	{
		j = 0;
		while (data->grid.grid[i][j])
		{
			draw_minimap_cell(data, params, i, j);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_data *data)
{
	t_minimap_params	params;

	calculate_minimap_params(data, &params);
	draw_minimap_grid(data, &params);
	draw_minimap_player_with_direction(data, &params);
}
