/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_init_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:21:07 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/27 13:25:31 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data, char **argv)
{
	if (parse_file(argv[1], data))
		close_window(data);
	data->render_fog = 1;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
	init_walls(data);
	init_mouse_control(data);
	data->player.stamina = MAX_STAMINA;
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
