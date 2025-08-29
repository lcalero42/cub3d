/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_determine_movement_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:48:15 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/29 08:03:56 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	determine_movement(t_data *data, double move_speed);
static void	determine_rotation(t_data *data, double rotation_speed);

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
	move_speed = u_get_current_speed(data) * delta_time;
	rotation_speed = ROTATION_SPEED * delta_time;
	determine_rotation(data, rotation_speed);
	determine_movement(data, move_speed);
	if (data->keys.run && data->player.stamina > 0)
		data->player.is_running = 1;
	else if (!data->keys.run)
		data->player.is_running = 0;
	update_player_stamina_status(data, delta_time);
}

void	handle_forward_backward(t_data *data, t_vector *move,
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

void	handle_strafe(t_data *data, t_vector *move, double move_speed)
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

static void	determine_movement(t_data *data, double move_speed)
{
	t_vector	move;
	t_vector	x_move;
	t_vector	y_move;
	double		magnitude;

	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	move.x = 0.0;
	move.y = 0.0;
	normalize_movement(data, &move, &magnitude, move_speed);
	if (!check_collisions(data, move))
	{
		data->player.position.x += move.x;
		data->player.position.y += move.y;
		return ;
	}
	x_move.x = move.x;
	x_move.y = 0;
	if (!check_collisions(data, x_move))
		data->player.position.x += move.x;
	y_move.x = 0;
	y_move.y = move.y;
	if (!check_collisions(data, y_move))
		data->player.position.y += move.y;
}

static void	determine_rotation(t_data *data, double rotation_speed)
{
	if (data->keys.left)
		data->player.angle -= rotation_speed;
	if (data->keys.right)
		data->player.angle += rotation_speed;
}
