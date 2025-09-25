/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:45:42 by ekeisler          #+#    #+#             */
/*   Updated: 2025/09/25 15:15:07 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void draw_minimap_background(t_data *data, int start_x, int start_y, int size);
static void draw_square(t_data *data, int x, int y, int color, int scale);

void	render_minimap(t_data *data)
{
    int	minimap_size;
    int	minimap_margin;
    int	cell_size;
    int	start_x;
    int	start_y;
    int	i;
    int	j;
    int	pixel_x;
    int	pixel_y;

    cell_size = WINDOW_WIDTH / 80;
    if (cell_size < 8)
        cell_size = 8;
    if (cell_size > 20)
        cell_size = 20;
    minimap_margin = WINDOW_WIDTH / 100;
    minimap_size = fmax(data->grid.width, data->grid.height) * cell_size;
    start_x = minimap_margin;
    start_y = minimap_margin;
    draw_minimap_background(data, start_x, start_y, minimap_size);
    i = 0;
    while (data->grid.grid[i])
    {
        j = 0;
        while (data->grid.grid[i][j])
        {
            pixel_x = start_x + j * cell_size;
            pixel_y = start_y + i * cell_size;
            if (data->grid.grid[i][j] == '1')
                draw_square(data, pixel_x, pixel_y, 0x000000, cell_size);
            else if (data->grid.grid[i][j] == '0')
                draw_square(data, pixel_x, pixel_y, 0xFFFFFF, cell_size);
            else if (data->grid.grid[i][j] == 'S')
                draw_square(data, pixel_x, pixel_y, 0x0F0F00, cell_size);
            j++;
        }
        i++;
    }
}

static void	draw_minimap_background(t_data *data, int start_x, int start_y, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel_to_image(data, start_x + x, start_y + y, 0x404040);
			x++;
		}
		y++;
	}
}

static void	draw_square(t_data *data, int x, int y, int color, int scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			put_pixel_to_image(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}