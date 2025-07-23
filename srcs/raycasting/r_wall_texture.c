/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wall_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:10:47 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/23 11:39:22 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_wall_texture(t_data *data, char *path, t_wall_render *wall);

void	init_walls(t_data *data)
{
	load_wall_texture(data, data->north_wall.info.addr, &data->north_wall);
	load_wall_texture(data, data->south_wall.info.addr, &data->south_wall);
	load_wall_texture(data, data->west_wall.info.addr, &data->west_wall);
	load_wall_texture(data, data->east_wall.info.addr, &data->east_wall);
	data->render_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->render_img)
	{
		printf("Error: Cannot create render buffer\n");
		exit(1);
	}
	data->render_addr = mlx_get_data_addr(data->render_img,
			&data->render_bpp,
			&data->render_line_len,
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
		return (0x87CEEB);
	side = get_wall_side(data, ray_index);
	texture = get_texture_info_by_side(data, side);
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
	dst = data->render_addr + (y * data->render_line_len
			+ x * (data->render_bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_screen(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_to_image(data, x, y, 0x87CEEB);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_to_image(data, x, y, 0x8B4513);
			x++;
		}
		y++;
	}
}

static void	load_wall_texture(t_data *data, char *path, t_wall_render *wall)
{
	int	width;
	int	height;

	wall->wall_texture_img = mlx_xpm_file_to_image(data->mlx, path,
			&width, &height);
	if (!wall->wall_texture_img)
	{
		printf("Error: Cannot load wall texture\n");
		exit(1);
	}
	wall->info.addr = mlx_get_data_addr(wall->wall_texture_img,
			&wall->info.bpp,
			&wall->info.line_len,
			&wall->wall_texture_endian);
}
