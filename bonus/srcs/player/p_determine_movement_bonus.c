/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_determine_movement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:48:15 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/29 15:55:29 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	determine_movement(t_data *data, double move_speed);
static void	determine_rotation(t_data *data, double rotation_speed);
static void	handle_forward_backward(t_data *data, t_vector *move,
				double move_speed);
static void	handle_strafe(t_data *data, t_vector *move, double move_speed);

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
	determine_rotation(data, rotation_speed);
	determine_movement(data, move_speed);
}

static void	determine_movement(t_data *data, double move_speed)
{
	t_vector	move;
	double		magnitude;

	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	move.x = 0.0;
	move.y = 0.0;
	handle_forward_backward(data, &move, move_speed);
	handle_strafe(data, &move, move_speed);
	magnitude = sqrt(move.x * move.x + move.y * move.y);
	if (magnitude > move_speed)
	{
		move.x = (move.x / magnitude) * move_speed;
		move.y = (move.y / magnitude) * move_speed;
	}
	data->player.position.x += move.x;
	data->player.position.y += move.y;
}

static void	determine_rotation(t_data *data, double rotation_speed)
{
	if (data->keys.left)
		data->player.angle -= rotation_speed;
	if (data->keys.right)
		data->player.angle += rotation_speed;
}

static void	handle_forward_backward(t_data *data, t_vector *move,
	double move_speed)
{
	if (data->keys.w)
	{
		move->x += data->player.dir.x * move_speed;
		move->y += data->player.dir.y * move_speed;
	}
	if (data->keys.s)
	{
		move->x -= data->player.dir.x * move_speed;
		move->y -= data->player.dir.y * move_speed;
	}
}

static void	handle_strafe(t_data *data, t_vector *move, double move_speed)
{
	double	strafe_speed;

	strafe_speed = move_speed * 0.7;
	if (data->keys.d)
	{
		move->x += (-data->player.dir.y) * strafe_speed;
		move->y += data->player.dir.x * strafe_speed;
	}
	if (data->keys.a)
	{
		move->x += data->player.dir.y * strafe_speed;
		move->y += (-data->player.dir.x) * strafe_speed;
	}
}
