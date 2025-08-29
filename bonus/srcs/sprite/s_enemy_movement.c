/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_enemy_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:53:18 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/28 19:37:57 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void update_enemy_movement(t_data *data)
{
	static long long last_update_time = 0;
	long long current_time;
	double delta_time;
	double move_speed;

	current_time = get_current_time();
	if (last_update_time == 0)
	{
		last_update_time = current_time;
		return ;
	}
	delta_time = (current_time - last_update_time) / 1000.0;
	last_update_time = current_time;
	move_speed = ENEMY_SPEED * delta_time;
	t_pos start = { (int)data->enemy.position.x, (int)data->enemy.position.y };
	t_pos goal = { (int)data->player.position.x, (int)data->player.position.y };
	t_pos path[128];
	int path_len = find_astar_path(data, start, goal, path, 128);
	if (path_len >= 2)
	{
		double target_x = path[1].x + 0.5;
		double target_y = path[1].y + 0.5;
		double dx = target_x - data->enemy.position.x;
		double dy = target_y - data->enemy.position.y;
		double distance = sqrt(dx * dx + dy * dy);
		if (distance > 0.01)
		{
			double norm_dx = dx / distance;
			double norm_dy = dy / distance;
			double next_x = data->enemy.position.x + norm_dx * move_speed;
			double next_y = data->enemy.position.y + norm_dy * move_speed;
			if (is_valid_position(data, next_x, next_y))
			{
				data->enemy.position.x = next_x;
				data->enemy.position.y = next_y;
			}
		}
	}
}
