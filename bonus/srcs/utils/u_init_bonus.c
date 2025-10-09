/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_init_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:20:59 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/09 13:47:47 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <time.h>

static void		spawn_enemy(t_data *data);

void	init(t_data *data, char **argv)
{
	srand(time(NULL));
	if (parse_file(argv[1], data))
		close_window(data);
	data->render_fog = 1;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	init_walls(data);
	load_texture(data, data->enemy_render.texture_path, &data->enemy.render);
	load_texture(data, "bonus/textures/gun-hand-0.xpm",
		&data->gun.render_arr[0]);
	load_texture(data, "bonus/textures/gun-hand-1.xpm",
		&data->gun.render_arr[1]);
	load_texture(data, "bonus/textures/gun-hand-2.xpm",
		&data->gun.render_arr[2]);
	load_texture(data, "bonus/textures/shot-0.xpm", &data->shot.render_arr[0]);
	load_texture(data, "bonus/textures/shot-1.xpm", &data->shot.render_arr[1]);
	load_texture(data, "bonus/textures/shot-2.xpm", &data->shot.render_arr[2]);
	init_door_system(data);
	data->gun.is_playing = 1;
	spawn_enemy(data);
	init_mouse_control(data);
	data->player.stamina = MAX_STAMINA;
	init_health_bar(&data->health_bar, data);
}

void	load_texture(t_data *data, char *path, t_render *texture)
{
	int	width;
	int	height;

	texture->texture_img = mlx_xpm_file_to_image(data->mlx, path, &width,
			&height);
	if (!texture->texture_img)
	{
		u_print_error("Cannot load wall texture");
		exit(1);
	}
	texture->info.addr = mlx_get_data_addr(texture->texture_img,
			&texture->info.bpp, &texture->info.line_len,
			&texture->texture_endian);
}

t_sprite_params	init_sprite_params(t_texture_info *info, int spr_top,
		int spr_height)
{
	t_sprite_params	params;

	params.tex_info = info;
	params.sprite_height = spr_height;
	params.sprite_top = spr_top;
	return (params);
}

static void	spawn_enemy(t_data *data)
{
	double	pos_x;
	double	pos_y;

	data->enemy.position.x = rand() % (data->grid.width);
	data->enemy.position.y = rand() % (data->grid.height);
	pos_x = data->enemy.position.x;
	pos_y = data->enemy.position.y;
	while (data->grid.grid[(int)pos_y][(int)pos_x] != '0'
			&& data->grid.grid[(int)pos_y][(int)pos_x])
	{
		data->enemy.position.x = rand() % (data->grid.width);
		data->enemy.position.y = rand() % (data->grid.height);
		pos_x = data->enemy.position.x;
		pos_y = data->enemy.position.y;
	}
	data->enemy.current_health = 100;
	data->enemy.max_health = 100;
}
