/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_get_wall_texture_pixel_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:07:25 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/14 13:13:49 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_pixel_from_texture(t_texture_info texture, int x, int y)
{
	char	*dst;

	if (!texture.addr)
		return (0x808080);
	dst = texture.addr + (y * texture.line_len + x * (texture.bpp / 8));
	return (*(unsigned int *)dst);
}

static t_texture_info	get_door_tex(t_data *data, t_pos pos)
{
	t_door			*door;
	t_texture_info	tex;

	door = &data->door_grid[pos.y][pos.x];
	if (!door)
	{
		tex.addr = NULL;
		return (tex);
	}
	return (get_door_texture(data, door));
}

static t_texture_info	get_texture_by_hit(t_data *data,
							int ray_index, int index_hit)
{
	int				hit_type;
	t_pos			pos;
	int				stored_side;
	t_wall_side		side;
	t_texture_info	tex;

	hit_type = data->rays[ray_index].hit[index_hit];
	pos = data->rays[ray_index].hit_map_pos[index_hit];
	stored_side = data->rays[ray_index].side_per_hit[index_hit];
	if (hit_type == 2)
		return (get_door_tex(data, pos));
	else if (hit_type == 1)
	{
		side = get_wall_side_from_stored(stored_side, data, ray_index);
		return (get_texture_info_by_side(data, side));
	}
	tex.addr = NULL;
	return (tex);
}

int	get_wall_texture_pixel(t_data *data, int y,
	int ray_index, int index_hit)
{
	t_texture_info	texture;
	int				tex_x;

	tex_x = calculate_texture_x_for_hit(data, ray_index, index_hit);
	if (tex_x < 0 || tex_x >= 64 || y < 0 || y >= 64)
		return (0x808080);
	if (!data->rays[ray_index].must_render)
		return (u_rgb_to_hex(data->ceiling.base_r,
				data->ceiling.base_g, data->ceiling.base_b, 255));
	texture = get_texture_by_hit(data, ray_index, index_hit);
	return (get_pixel_from_texture(texture, tex_x, y));
}
