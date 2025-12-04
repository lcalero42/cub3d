/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sprite_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:04:02 by lcalero           #+#    #+#             */
/*   Updated: 2025/12/04 18:25:32 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

static unsigned int	get_texture_pixel(t_texture_info *texture_info,
						int x, int y);

void	calculate_sprite_bounds(int screen_x, int sprite_height,
	t_sprite_bounds *bounds)
{
	int	half_width;

	half_width = sprite_height >> 1;
	bounds->start_x = screen_x - half_width;
	bounds->end_x = screen_x + half_width;
	bounds->half_width = half_width;
	if (bounds->start_x < 0)
		bounds->start_x = 0;
	if (bounds->end_x >= WINDOW_WIDTH)
		bounds->end_x = WINDOW_WIDTH - 1;
}

void	draw_sprite_column(t_data *data, t_sprite_params *params,
			t_sprite_bounds *bounds)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	y = params->sprite_top;
	while (y < params->sprite_top + params->sprite_height
		&& y < WINDOW_HEIGHT)
	{
		if (y < 0)
		{
			y++;
			continue ;
		}
		tex_y = (int)((float)(y - params->sprite_top) * bounds->sprite_size
				/ params->sprite_height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= bounds->sprite_size)
			tex_y = bounds->sprite_size;
		color = get_texture_pixel(params->tex_info, params->tex_x, tex_y);
		if (!is_transparent_color(color))
			put_pixel_to_image(data, params->x, y, color);
		y++;
	}
}

static unsigned int	get_texture_pixel(t_texture_info *texture_info,
				int x, int y)
{
	int				bytes_per_pixel;
	char			*pixel_addr;
	unsigned char	rgba[4];
	unsigned int	color;

	bytes_per_pixel = texture_info->bpp >> 3;
	pixel_addr = texture_info->addr + y * texture_info->line_len
		+ x * bytes_per_pixel;
	rgba[2] = (unsigned char)pixel_addr[0];
	rgba[1] = (unsigned char)pixel_addr[1];
	rgba[0] = (unsigned char)pixel_addr[2];
	if (bytes_per_pixel == 4)
		rgba[3] = (unsigned char)pixel_addr[3];
	else
		rgba[3] = 255;
	color = ((rgba[3] << 24) | (rgba[0] << 16) | (rgba[1] << 8) | rgba[2]);
	return (color);
}

int	is_transparent_color(unsigned int color)
{
	if (color == 0x00FFFFFF)
		return (1);
	return (0);
}
