/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_hpad_sprite_calc_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:59:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/21 05:00:06 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_sprite_basic_data(t_generic_sprite *sprite, t_vector pos,
	void *data, double distance)
{
	sprite->type = SPRITE_HEALTH_PAD;
	sprite->position = pos;
	sprite->data = data;
	sprite->distance = distance;
}

static double	calc_inv_determinant(t_player *player)
{
	return (1.0 / (player->camera_segment.x * player->dir.y
			- player->dir.x * player->camera_segment.y));
}

static void	calc_sprite_transform(t_sprite_calc *calc, t_player *player,
	double inv_det)
{
	calc->transform_x = inv_det * (player->dir.y * calc->sprite_x
			- player->dir.x * calc->sprite_y);
	calc->transform_y = inv_det * (-player->camera_segment.y * calc->sprite_x
			+ player->camera_segment.x * calc->sprite_y);
}

static void	calc_sprite_screen_props(t_sprite_calc *calc)
{
	calc->screen_x = (int)((WINDOW_WIDTH / 2)
			* (1 + calc->transform_x / calc->transform_y));
	calc->sprite_height = abs((int)(WINDOW_HEIGHT / calc->transform_y));
	calc->sprite_width = abs((int)(WINDOW_HEIGHT / calc->transform_y));
}

void	add_health_pad_sprite(t_data *data, t_generic_sprite *sprites,
	int *count, int i)
{
	t_vector	pos;
	double		dx;
	double		dy;
	double		inv_det;

	pos.x = data->health_pad[i].pos.x + 0.5;
	pos.y = data->health_pad[i].pos.y + 0.5;
	dx = data->player.position.x - pos.x;
	dy = data->player.position.y - pos.y;
	init_sprite_basic_data(&sprites[*count], pos, &data->health_pad[i],
		sqrt(dx * dx + dy * dy));
	sprites[*count].calc.sprite_x = pos.x - data->player.position.x;
	sprites[*count].calc.sprite_y = pos.y - data->player.position.y;
	inv_det = calc_inv_determinant(&data->player);
	calc_sprite_transform(&sprites[*count].calc, &data->player, inv_det);
	if (sprites[*count].calc.transform_y <= 0.1)
		return ;
	calc_sprite_screen_props(&sprites[*count].calc);
	(*count)++;
}
