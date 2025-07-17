/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wall_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:10:47 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/17 18:08:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_wall_texture(t_data *data, char *path);

void	init_walls(t_data *data)
{
	load_wall_texture(data, "sprites/wall.xpm");
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

int	get_wall_texture_pixel(t_data *data, int x, int y, int side)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return (0x808080);
	dst = data->wall_texture_addr + (y * data->wall_texture_line_len
			+ x * (data->wall_texture_bpp / 8));
	color = *(unsigned int *)dst;
	if (side == 1)
		color = ((color >> 1) & 0x7F7F7F);
	return (color);
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

static void	load_wall_texture(t_data *data, char *path)
{
	int	width;
	int	height;

	data->wall_texture_img = mlx_xpm_file_to_image(data->mlx, path,
			&width, &height);
	if (!data->wall_texture_img)
	{
		printf("Error: Cannot load wall texture\n");
		exit(1);
	}
	data->wall_texture_addr = mlx_get_data_addr(data->wall_texture_img,
			&data->wall_texture_bpp,
			&data->wall_texture_line_len,
			&data->wall_texture_endian);
}
