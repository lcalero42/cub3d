/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_determine_movement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:48:15 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/28 14:03:39 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	determin_movement(t_data *data, double move_speed);
static void	determin_rotation(t_data *data, double rotation_speed);

void	update_player_movement(t_data *data)
{
	long long	current_time;
	double		delta_time;
	double		move_speed;
	double		rotation_speed;

	current_time = get_current_time();
	if (data->last_time == 0)
	{
		data->last_time = current_time;
		return ;
	}
	delta_time = (current_time - data->last_time) / 1000.0;
	data->last_time = current_time;
	move_speed = MOVE_SPEED * delta_time;
	rotation_speed = ROTATION_SPEED * delta_time;
	determin_rotation(data, rotation_speed);
	determin_movement(data, move_speed);
}

static void	determin_movement(t_data *data, double move_speed)
{
	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	if (data->keys.w)
	{
		data->player.position.x += move_speed * data->player.dir.x;
		data->player.position.y += move_speed * data->player.dir.y;
	}
	if (data->keys.s)
	{
		data->player.position.x -= move_speed * data->player.dir.x;
		data->player.position.y -= move_speed * data->player.dir.y;
	}
	if (data->keys.d)
	{
		data->player.position.x += move_speed * (-data->player.dir.y);
		data->player.position.y += move_speed * data->player.dir.x;
	}
	if (data->keys.a)
	{
		data->player.position.x += move_speed * data->player.dir.y;
		data->player.position.y += move_speed * (-data->player.dir.x);
	}
}

static void	determin_rotation(t_data *data, double rotation_speed)
{
	if (data->keys.left)
		data->player.angle -= rotation_speed;
	if (data->keys.right)
		data->player.angle += rotation_speed;
}
