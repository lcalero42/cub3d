/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rendering_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:25:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/24 16:50:03 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_wall_texture_pixel(t_data *data, int x, int y, int ray_index)
{
	t_texture_info	texture;
	t_wall_side		side;
	char			*dst;

	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return (0x808080);
	if (!data->rays[ray_index].must_render)
		return (u_rgb_to_hex(data->ceiling.base_r,
				data->ceiling.base_g, data->ceiling.base_b, 255));
	side = get_wall_side(data, ray_index);
	texture = get_texture_info_by_side(data, side);
	if (data->rays[ray_index].hit == 2)
		texture = get_door_texture(data, find_door_at(data, data->rays[ray_index].map_pos.x, data->rays[ray_index].map_pos.y));
	if (!texture.addr)
		return (0x808080);
	dst = texture.addr + (y * texture.line_len + x * (texture.bpp / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->render_info.addr + (y * data->render_info.line_len
			+ x * (data->render_info.bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_from_image(t_data *data, int x, int y)
{
	char	*pixel_addr;
	int		color;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return (0);
	pixel_addr = data->render_info.addr + y * data->render_info.line_len + x
		* (data->render_info.bpp / 8);
	color = *(unsigned int *)pixel_addr;
	return (color);
}

int	blend_colors(t_color *colors, double alpha)
{
	int	r;
	int	g;
	int	b;

	r = (int)(colors->base_r * (1.0 - alpha) + colors->fog_r * alpha);
	g = (int)(colors->base_g * (1.0 - alpha) + colors->fog_g * alpha);
	b = (int)(colors->base_b * (1.0 - alpha) + colors->fog_b * alpha);
	return ((r << 16) | (g << 8) | b);
}

void	extract_base_colors(int base_color, int *r, int *g, int *b)
{
	*r = (base_color >> 16) & 0xFF;
	*g = (base_color >> 8) & 0xFF;
	*b = base_color & 0xFF;
}
