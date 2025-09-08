/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_wall_texture_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:10:47 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/08 14:50:40 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_walls(t_data *data)
{
	load_texture(data, data->north_wall.texture_path, &data->north_wall);
	load_texture(data, data->south_wall.texture_path, &data->south_wall);
	load_texture(data, data->west_wall.texture_path, &data->west_wall);
	load_texture(data, data->east_wall.texture_path, &data->east_wall);
	load_texture(data, "bonus/textures/door-open.xpm", &data->door_opened);
	data->render_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->render_img)
	{
		printf("Error: Cannot create render buffer\n");
		exit(1);
	}
	data->render_info.addr = mlx_get_data_addr(data->render_img,
			&data->render_info.bpp,
			&data->render_info.line_len,
			&data->render_endian);
}

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
	{
		texture.addr = data->door_opened.info.addr;
		texture.bpp = data->door_opened.info.bpp;
		texture.line_len = data->door_opened.info.line_len;
	}
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

void	clear_screen(t_data *data)
{
	int		x;
	int		y;
	int		horizon_line;

	horizon_line = calc_horizon_line(data);
	y = 0;
	while (y < horizon_line)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_to_image(
				data, x, y,
				u_rgb_to_hex(data->ceiling.base_r, data->ceiling.base_g,
					data->ceiling.base_b, 0));
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		draw_floor(data, 0, y);
		y++;
	}
}

int	calc_horizon_line(t_data *data)
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
