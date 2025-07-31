/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rendering_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:25:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/31 17:23:21 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	blend_component(int base, int fog, double alpha);

void	draw_floor(t_data *data, int start_x, int y)
{
	float	t;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	double	pitch_offset;
	int		adjusted_horizon;
	int		x;
	int		floor_height;

	pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);
	adjusted_horizon = WINDOW_HEIGHT / 2 + (int)pitch_offset;
	if (adjusted_horizon < 0)
		adjusted_horizon = 0;
	if (adjusted_horizon >= WINDOW_HEIGHT)
		adjusted_horizon = WINDOW_HEIGHT - 1;
	if (y <= adjusted_horizon)
		return ;
	floor_height = WINDOW_HEIGHT - adjusted_horizon;
	if (floor_height <= 0)
		floor_height = 1;
	t = (float)(y - adjusted_horizon) / (float)floor_height;
	if (t > 1.0f)
		t = 1.0f;
	if (t < 0.0f)
		t = 0.0f;
	if (data->render_fog)
	{
		floor_r = (int)(data->floor.base_r * (0.3f + 0.7f * t));
		floor_g = (int)(data->floor.base_g * (0.3f + 0.7f * t));
		floor_b = (int)(data->floor.base_b * (0.3f + 0.7f * t));
	}
	else
	{
		floor_r = data->floor.base_r;
		floor_g = data->floor.base_g;
		floor_b = data->floor.base_b;
	}
	x = start_x;
	while (x < WINDOW_WIDTH)
	{
		put_pixel_to_image(data, x, y,
			u_rgb_to_hex(floor_r, floor_g, floor_b, 0));
		x++;
	}
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
