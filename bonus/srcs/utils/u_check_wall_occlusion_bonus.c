/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_check_wall_occlusion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:09:40 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/09 15:26:08 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	calculate_enemy_distance(t_enemy *enemy, t_player *player)
{
	double	dx;
	double	dy;

	dx = enemy->position.x - player->position.x;
	dy = enemy->position.y - player->position.y;
	return (sqrt(dx * dx + dy * dy));
}

static void	calculate_sprite_screen_bounds(t_enemy *enemy,
	int *sprite_top, int *sprite_bottom)
{
	*sprite_top = enemy->enemy_data.sprite_top;
	*sprite_bottom = *sprite_top + enemy->enemy_data.sprite_height;
	if (*sprite_top < 0)
		*sprite_top = 0;
	if (*sprite_bottom > WINDOW_HEIGHT)
		*sprite_bottom = WINDOW_HEIGHT;
}

static int	check_door_occlusion_at_ray(t_data *data, int x,
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

static int	check_hit_occlusion(t_data *data, int x,
	int i, t_occlusion_data *occ_data)
{
	double	wall_distance;
	int		hit_type;

	wall_distance = data->rays[x].perp_wall_dist_per_hit[i];
	hit_type = data->rays[x].hit[i];
	if (wall_distance >= occ_data->enemy_distance)
		return (0);
	if (hit_type == 1)
		return (1);
	if (hit_type == 2)
		return (check_door_occlusion_at_ray(data, x, i,
				occ_data->sprite_bounds));
	return (0);
}

int	check_wall_occlusion(t_data *data, int x, t_enemy *enemy)
{
	t_occlusion_data	occ_data;
	int					i;

	if (x < 0 || x >= WINDOW_WIDTH)
		return (1);
	occ_data.enemy_distance = calculate_enemy_distance(enemy,
			&data->player);
	calculate_sprite_screen_bounds(enemy, &occ_data.sprite_bounds[0],
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
