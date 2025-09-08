/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sprite_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:04:02 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/08 16:33:51 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

unsigned int	get_texture_pixel(t_texture_info *texture_info, int x, int y)
{
	int				bytes_per_pixel;
	char			*pixel_addr;
	unsigned char	rgba[4];
	unsigned int	color;

	bytes_per_pixel = texture_info->bpp / 8;
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

void	calculate_sprite_bounds(int screen_x, int sprite_height,
	t_sprite_bounds *bounds)
{
	int	half_width;

	half_width = sprite_height / 2;
	bounds->start_x = screen_x - half_width;
	bounds->end_x = screen_x + half_width;
	bounds->half_width = half_width;
	if (bounds->start_x < 0)
		bounds->start_x = 0;
	if (bounds->end_x >= WINDOW_WIDTH)
		bounds->end_x = WINDOW_WIDTH - 1;
}

void	draw_sprite_column(t_data *data, t_sprite_params *params)
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
		tex_y = (int)((float)(y - params->sprite_top) * 64
				/ params->sprite_height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= 64)
			tex_y = 64 - 1;
		color = get_texture_pixel(params->tex_info, params->tex_x, tex_y);
		if (!is_transparent_color(color))
			put_pixel_to_image(data, params->x, y, color);
		y++;
	}
}

int	check_wall_occlusion(t_data *data, int x, t_enemy *enemy)
{
	float	player_dist;
	float	wall_dist;

	if (data->rays[x].hit != 1 && data->rays[x].hit != 2
		&& data->rays[x].hit != 3)
		return (0);
	player_dist = sqrtf((enemy->position.x - data->player.position.x)
			* (enemy->position.x - data->player.position.x)
			+ (enemy->position.y - data->player.position.y)
			* (enemy->position.y - data->player.position.y));
	wall_dist = data->rays[x].perp_wall_dist;
	return (wall_dist < player_dist);
}
