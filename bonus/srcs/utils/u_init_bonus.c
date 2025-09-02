/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_init_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:21:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 16:12:33 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init(t_data *data, char **argv)
{
	if (parse_file(argv[1], data))
		close_window(data);
	data->render_fog = 1;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
	init_walls(data);
	load_texture(data, "bonus/textures/enemy_jaurel.xpm", &data->enemy.render);
	data->enemy.position.x = data->player.position.x + 1.0;
	data->enemy.position.y = data->player.position.y + 1.0;
	init_mouse_control(data);
}

void	load_texture(t_data *data, char *path, t_render *texture)
{
	int	width;
	int	height;

	texture->texture_img = mlx_xpm_file_to_image(data->mlx, path,
			&width, &height);
	if (!texture->texture_img)
	{
		printf("Error: Cannot load wall texture\n");
		exit(1);
	}
	texture->info.addr = mlx_get_data_addr(texture->texture_img,
			&texture->info.bpp,
			&texture->info.line_len,
			&texture->texture_endian);
}

t_sprite_params	init_sprite_params(t_texture_info *info,
					int spr_top, int spr_height)
{
	t_sprite_params	params;

	params.tex_info = info;
	params.sprite_height = spr_height;
	params.sprite_top = spr_top;
	return (params);
}
