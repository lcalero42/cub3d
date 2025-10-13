/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_wall_texture_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:10:47 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/01 14:49:24 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	calc_horizon_line(t_data *data);
static void	draw_floor_line_with_fog(t_data *data, int y, int horizon_line);

void	clear_screen(t_data *data)
{
	int	y;
	int	horizon_line;

	horizon_line = calc_horizon_line(data);
	y = 0;
	while (y < horizon_line)
	{
		draw_sky_line_with_fog(data, y, horizon_line);
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		draw_floor_line_with_fog(data, y, horizon_line);
		y++;
	}
}

void	init_walls(t_data *data)
{
	load_texture(data, data->north_wall.texture_path, &data->north_wall);
	load_texture(data, data->south_wall.texture_path, &data->south_wall);
	load_texture(data, data->west_wall.texture_path, &data->west_wall);
	load_texture(data, data->east_wall.texture_path, &data->east_wall);
	load_texture(data, "bonus/textures/door-open.xpm", &data->door_closed);
	load_texture(data, "bonus/textures/door-closed.xpm", &data->door_opened);
	data->render_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->render_img)
	{
		printf("Error: Cannot create render buffer\n");
		exit(1);
	}
	data->render_info.addr = mlx_get_data_addr(data->render_img,
			&data->render_info.bpp, &data->render_info.line_len,
			&data->render_endian);
}

static void	draw_floor_line_with_fog(t_data *data, int y, int horizon_line)
{
	int	x;
	int	fog_alpha;
	int	base_color;
	int	fog_color;
	int	final_color;

	fog_alpha = calculate_ground_fog_alpha(y, horizon_line);
	base_color = u_rgb_to_hex(data->floor.base_r, data->floor.base_g,
			data->floor.base_b, 255);
	fog_color = u_rgb_to_hex(FOG_COLOR_R, FOG_COLOR_G, FOG_COLOR_B, 255);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		if (fog_alpha > 0)
			final_color = blend_fog_with_pixel(base_color,
					fog_color, fog_alpha);
		else
			final_color = base_color;
		put_pixel_to_image(data, x, y, final_color);
		x++;
	}
}

static int	calc_horizon_line(t_data *data)
{
	int		horizon_line;

	data->player.pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);
	horizon_line = WINDOW_HEIGHT / 2 + (int)data->player.pitch_offset;
	if (horizon_line < 0)
		horizon_line = 0;
	if (horizon_line >= WINDOW_HEIGHT)
		horizon_line = WINDOW_HEIGHT - 1;
	return (horizon_line);
}
