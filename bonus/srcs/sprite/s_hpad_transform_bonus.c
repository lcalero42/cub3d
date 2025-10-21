/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_hpad_transform_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:11:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/21 01:03:17 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_sprite_position(t_data *data, t_generic_sprite *sprite)
{
	double	sprite_x;
	double	sprite_y;

	sprite_x = sprite->position.x - data->player.position.x;
	sprite_y = sprite->position.y - data->player.position.y;
	sprite->calc.inv_det = 1.0 / (data->player.camera_segment.x
			* data->player.dir.y - data->player.dir.x
			* data->player.camera_segment.y);
	sprite->calc.transform_x = sprite->calc.inv_det
		* (data->player.dir.y * sprite_x - data->player.dir.x * sprite_y);
	sprite->calc.transform_y = sprite->calc.inv_det
		* (-data->player.camera_segment.y * sprite_x
			+ data->player.camera_segment.x * sprite_y);
}

void	calculate_sprite_size(t_generic_sprite *sprite)
{
	double	scale;

	sprite->calc.screen_x = (int)((WINDOW_WIDTH / 2)
			* (1 + sprite->calc.transform_x / sprite->calc.transform_y));
	scale = 1.0;
	if (sprite->type == SPRITE_HEALTH_PAD)
		scale = 0.5;
	sprite->calc.sprite_height = abs((int)(WINDOW_HEIGHT
				/ sprite->calc.transform_y * scale));
	sprite->calc.sprite_width = abs((int)(WINDOW_HEIGHT
				/ sprite->calc.transform_y * scale));
}

void	calculate_sprite_transform(t_data *data, t_generic_sprite *sprite)
{
	calculate_sprite_position(data, sprite);
	if (sprite->calc.transform_y <= 0)
		return ;
	calculate_sprite_size(sprite);
	calculate_sprite_bounds_y(data, &sprite->calc);
	calculate_sprite_bounds_x(&sprite->calc);
}

int	check_sprite_occlusion(t_data *data, int x, t_vector sprite_pos,
	t_sprite_calc *calc)
{
	t_occlusion_data	occ_data;
	int					i;

	if (x < 0 || x >= WINDOW_WIDTH)
		return (1);
	occ_data.sprite_distance = calculate_sprite_distance(sprite_pos,
			&data->player);
	calculate_sprite_bounds_from_calc(calc, &occ_data.sprite_bounds[0],
		&occ_data.sprite_bounds[1]);
	i = 0;
	while (i < data->rays[x].index_hit)
	{
		if (check_hit_occlusion(data, x, i, &occ_data))
			return (1);
		i++;
	}
	return (0);
}
