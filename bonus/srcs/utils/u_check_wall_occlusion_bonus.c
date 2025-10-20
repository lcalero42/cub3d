/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_check_wall_occlusion_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:06:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/20 20:13:51 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	calculate_sprite_distance(t_vector sprite_pos, t_player *player)
{
	double	dx;
	double	dy;

	dx = sprite_pos.x - player->position.x;
	dy = sprite_pos.y - player->position.y;
	return (sqrt(dx * dx + dy * dy));
}

void	calculate_sprite_bounds_from_calc(t_sprite_calc *calc,
	int *sprite_top, int *sprite_bottom)
{
	*sprite_top = calc->draw_start_y;
	*sprite_bottom = calc->draw_end_y;
	if (*sprite_top < 0)
		*sprite_top = 0;
	if (*sprite_bottom > WINDOW_HEIGHT)
		*sprite_bottom = WINDOW_HEIGHT;
}

int	check_door_occlusion_at_ray(t_data *data, int x,
	int i, int sprite_bounds[2])
{
	int	sample_count;
	int	opaque_count;
	int	step_y;
	int	y;
	int	pixel;

	sample_count = 0;
	opaque_count = 0;
	step_y = (sprite_bounds[1] - sprite_bounds[0]) / 5;
	if (step_y < 1)
		step_y = 1;
	y = sprite_bounds[0];
	while (y < sprite_bounds[1])
	{
		pixel = get_door_pixel_at_position(data, x, y, i);
		if (pixel != -1)
		{
			sample_count++;
			if (!is_transparent_color(pixel))
				opaque_count++;
		}
		y += step_y;
	}
	return (sample_count > 0 && opaque_count * 2 > sample_count);
}

int	check_hit_occlusion(t_data *data, int x,
	int i, t_occlusion_data *occ_data)
{
	double	wall_distance;
	int		hit_type;

	wall_distance = data->rays[x].perp_wall_dist_per_hit[i];
	hit_type = data->rays[x].hit[i];
	if (wall_distance >= occ_data->sprite_distance)
		return (0);
	if (hit_type == 1)
		return (1);
	if (hit_type == 2)
		return (check_door_occlusion_at_ray(data, x, i,
				occ_data->sprite_bounds));
	return (0);
}

int	check_enemy_occlusion(t_data *data, int x, t_enemy *enemy)
{
	t_sprite_calc	calc;

	calc.draw_start_y = enemy->enemy_data.sprite_top;
	calc.draw_end_y = enemy->enemy_data.sprite_top
		+ enemy->enemy_data.sprite_height;
	return (check_sprite_occlusion(data, x, enemy->position, &calc));
}
