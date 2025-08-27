/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rendering_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:25:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/27 17:58:07 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	blend_component(int base, int fog, double alpha);

void	draw_floor(t_data *data, int x, int y)
{
	float	t;
	int		floor_r;
	int		floor_g;
	int		floor_b;

	t = (float)(y - WINDOW_HEIGHT / 2) / (WINDOW_HEIGHT / 2);
	if (t > 1.0f)
		t = 1.0f;
	if (t < 0.0f)
		t = 0.0f;
	if (data->render_fog)
	{
		floor_r = (int)(data->floor.base_r * t);
		floor_g = (int)(data->floor.base_g * t);
		floor_b = (int)(data->floor.base_b * t);
	}
	else
	{
		floor_r = data->floor.base_r;
		floor_g = data->floor.base_g;
		floor_b = data->floor.base_b;
	}
	while (x++ < WINDOW_WIDTH)
		put_pixel_to_image(data, x, y,
			u_rgb_to_hex(floor_r, floor_g, floor_b, 0));
}

int	get_pixel_from_image(t_data *data, int x, int y)
{
	char	*pixel_addr;
	int		color;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return (0);
	pixel_addr = data->render_info.addr + y * data->render_info.line_len
		+ x * (data->render_info.bpp / 8);
	color = *(unsigned int *)pixel_addr;
	return (color);
}

int	blend_colors(t_color *colors, double alpha)
{
	int	r;
	int	g;
	int	b;

	r = blend_component(colors->base_r, colors->fog_r, alpha);
	g = blend_component(colors->base_g, colors->fog_g, alpha);
	b = blend_component(colors->base_b, colors->fog_b, alpha);
	return ((r << 16) | (g << 8) | b);
}

void	extract_base_colors(int base_color, int *r, int *g, int *b)
{
	*r = (base_color >> 16) & 0xFF;
	*g = (base_color >> 8) & 0xFF;
	*b = base_color & 0xFF;
}

static int	blend_component(int base, int fog, double alpha)
{
	return ((int)(base * (1.0 - alpha) + fog * alpha));
}
