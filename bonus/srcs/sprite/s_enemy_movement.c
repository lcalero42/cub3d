/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_enemy_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:53:18 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 16:18:31 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	calculate_delta_time(void)
{
	static long long	last_update_time = 0;
	long long			current_time;
	double				delta_time;

	current_time = get_current_time();
	if (last_update_time == 0)
	{
		last_update_time = current_time;
		return (0.0);
	}
	delta_time = (current_time - last_update_time) / 1000.0;
	last_update_time = current_time;
	return (delta_time);
}

static void	init_movement_data(t_data *data, t_movement_data *move_data,
	double delta_time)
{
	move_data->move_speed = ENEMY_SPEED * delta_time;
	move_data->start.x = (int)data->enemy.position.x;
	move_data->start.y = (int)data->enemy.position.y;
	move_data->goal.x = (int)data->player.position.x;
	move_data->goal.y = (int)data->player.position.y;
}

static void	move_enemy_towards_target(t_data *data, t_pos target,
	double move_speed)
{
	double	target_x;
	double	target_y;
	double	dx;
	double	dy;
	double	distance;

	target_x = target.x + 0.5;
	target_y = target.y + 0.5;
	dx = target_x - data->enemy.position.x;
	dy = target_y - data->enemy.position.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > 0.01)
	{
		dx = (dx / distance) * move_speed;
		dy = (dy / distance) * move_speed;
		if (is_valid_position(data, data->enemy.position.x + dx,
				data->enemy.position.y + dy))
		{
			data->enemy.position.x += dx;
			data->enemy.position.y += dy;
		}
	}
}

void	update_enemy_movement(t_data *data)
{
	t_movement_data	move_data;
	double			delta_time;
	int				path_len;

	delta_time = calculate_delta_time();
	if (delta_time == 0.0)
		return ;
	init_movement_data(data, &move_data, delta_time);
	path_len = find_astar_path(data, move_data.start, move_data.goal,
			move_data.path);
	if (path_len >= 2)
		move_enemy_towards_target(data, move_data.path[1],
			move_data.move_speed);
}
