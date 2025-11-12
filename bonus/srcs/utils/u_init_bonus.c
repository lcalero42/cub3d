/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_init_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:20:59 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/10 17:20:52 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <time.h>

static void		load_sprites(t_data *data);

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
	data->door_count = 0;
	data->health_count = 0;
	load_sprites(data);
	data->gun.is_playing = 1;
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
		close_window(data);
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

void	spawn_enemy(t_data *data)
{
	int	x;
	int	y;
	int	attempts;

	attempts = 0;
	while (attempts < 1000)
	{
		y = rand() % data->grid.height;
		x = rand() % data->grid.width;
		if (is_valid_spawn(data, x, y))
		{
			data->enemy.position.x = (double)x;
			data->enemy.position.y = (double)y;
			data->enemy.current_health = 100;
			data->enemy.max_health = 100;
			return ;
		}
		attempts++;
	}
	printf("Error: Could not find valid spawn position\n");
}

static void	load_sprites(t_data *data)
{
	load_texture(data, data->enemy_render.texture_path, &data->enemy.render);
	load_texture(data, "bonus/textures/gun-hand-0.xpm",
		&data->gun.render_arr[0]);
	load_texture(data, "bonus/textures/gun-hand-1.xpm",
		&data->gun.render_arr[1]);
	load_texture(data, "bonus/textures/gun-hand-2.xpm",
		&data->gun.render_arr[2]);
	load_texture(data, "bonus/textures/heal_1.xpm",
		&data->health_pad_anim.render_arr[0]);
	load_texture(data, "bonus/textures/heal_2.xpm",
		&data->health_pad_anim.render_arr[1]);
	load_texture(data, "bonus/textures/heal_3.xpm",
		&data->health_pad_anim.render_arr[2]);
	load_texture(data, "bonus/textures/shot-0.xpm", &data->shot.render_arr[0]);
	load_texture(data, "bonus/textures/shot-1.xpm", &data->shot.render_arr[1]);
	load_texture(data, "bonus/textures/shot-2.xpm", &data->shot.render_arr[2]);
	load_texture(data, "bonus/textures/play_button.xpm", &data->play_button);
	load_texture(data, "bonus/textures/leave_button.xpm", &data->leave_button);
	load_texture(data, "bonus/textures/menu_background.xpm",
		&data->menu_background);
	load_texture(data, "bonus/textures/game_over_print.xpm",
		&data->game_over_print);
	load_texture(data, "bonus/textures/you_won_print.xpm",
		&data->you_won_print);
}
