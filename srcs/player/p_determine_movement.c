/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_determine_movement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:48:15 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/24 15:33:52 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int set_player_moving(t_data *data);

void	update_player_movement(t_data *data, t_player *player, t_time *time)
{
	double frame_move_speed;
	double frame_rot_speed;
	double move_x = 0.0;
	double move_y = 0.0;
	int moving = 0;
	
	move_x = 0.0;
	move_y = 0.0;
	frame_move_speed = MOVE_SPEED * time->delta_time;
	frame_rot_speed = (ROTATION_SPEED * (M_PI)) * time->delta_time;
	if (data->keys.left)
		player->angle -= frame_rot_speed;
	if (data->keys.right)
		player->angle += frame_rot_speed;
	player->angle = fmod(player->angle + 2 * M_PI, 2 * M_PI);
	player->dir.x = cos(player->angle);
	player->dir.y = sin(player->angle);
	moving = set_player_moving(data);
	if (data->keys.w)
	{
		move_x += player->dir.x;
		move_y += player->dir.y;
	}
	if (data->keys.s)
	{
		move_x -= player->dir.x;
		move_y -= player->dir.y;
	}
	if (data->keys.d)
	{
		move_x += (-player->dir.y);
		move_y += player->dir.x;
	}
	if (data->keys.a)
	{
		move_x += player->dir.y;
		move_y += (-player->dir.x);
	}
	
	// Normalize diagonal movement
	if (moving)
	{
		double magnitude = sqrt(move_x * move_x + move_y * move_y);
		if (magnitude > 0)
		{
			move_x = (move_x / magnitude) * frame_move_speed;
			move_y = (move_y / magnitude) * frame_move_speed;
			
			// Apply the normalized movement
			player->position.x += move_x;
			player->position.y += move_y;
		}
	}
}

static int set_player_moving(t_data *data)
{
	return (data->keys.w || data->keys.s || data->keys.d || data->keys.a);
}
