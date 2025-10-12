/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rendering_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:25:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/12 21:12:49 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_wall_side	get_wall_side_from_stored(int stored_side,
				t_data *data, int ray_index)
{
	if (stored_side == 0)
	{
		if (data->rays[ray_index].ray_dir.x > 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (data->rays[ray_index].ray_dir.y > 0)
			return (NORTH);
		else
			return (SOUTH);
	}
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
