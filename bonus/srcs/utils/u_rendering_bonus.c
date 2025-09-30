/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rendering_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:25:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/30 20:05:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int get_wall_texture_pixel(t_data *data, int x, int y, int ray_index, int index_hit)
{
    t_texture_info  texture;
    t_wall_side     side;
    char            *dst;

    if (x < 0 || x >= 64 || y < 0 || y >= 64)
        return (0x808080);
    if (!data->rays[ray_index].must_render)
        return (u_rgb_to_hex(data->ceiling.base_r,
                data->ceiling.base_g, data->ceiling.base_b, 255));
    int hit_type = data->rays[ray_index].hit[index_hit];
    t_pos pos = data->rays[ray_index].hit_map_pos[index_hit];
	if (ray_index == WINDOW_WIDTH / 2)
		printf("HIT_TYPE  AAAAA: %d\n", data->rays[WINDOW_WIDTH / 2].hit[data->rays[WINDOW_WIDTH / 2].index_hit - 2]);
    if (hit_type == 2)
    {
		t_door *door = find_door_at(data, pos.x, pos.y);
		if (ray_index == WINDOW_WIDTH / 2)
			printf("STATE : %d\n", door->state);
        if (!door)
			return (0x808080);
        texture = get_door_texture(data, door);
    }
    else if (hit_type == 1)
    {
		side = get_wall_side(data, ray_index);
        texture = get_texture_info_by_side(data, side);
    }
    else
        return (0x808080);
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
