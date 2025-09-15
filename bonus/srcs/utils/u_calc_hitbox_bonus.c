/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_calc_hitbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:23:49 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/11 13:49:18 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calc_discriminant(t_data *data);

int	ray_hits_enemy(t_data *data)
{
	double	t;

	data->disc.dx = data->enemy.position.x - data->player.position.x;
	data->disc.dy = data->enemy.position.y - data->player.position.y;
	data->disc.ray_dx = data->shot_ray.ray_dir.x + data->player.pitch;
	data->disc.ray_dy = data->shot_ray.ray_dir.y + data->player.pitch;
	calc_discriminant(data);
	if (data->disc.discriminant < 0)
		return (0);
	t = (-data->disc.b - sqrt(data->disc.discriminant)) / (2 * data->disc.a);
	return (t > 0);
}

static void	calc_discriminant(t_data *data)
{
	data->disc.a = data->disc.ray_dx * data->disc.ray_dx + data->disc.ray_dy
		* data->disc.ray_dy;
	data->disc.b = 2 * (data->disc.ray_dx * (-data->disc.dx) + data->disc.ray_dy
			* (-data->disc.dy));
	data->disc.c = data->disc.dx * data->disc.dx + data->disc.dy * data->disc.dy
		- ENEMY_RADIUS * ENEMY_RADIUS;
	data->disc.discriminant = data->disc.b * data->disc.b - 4 * data->disc.a
		* data->disc.c;
}
