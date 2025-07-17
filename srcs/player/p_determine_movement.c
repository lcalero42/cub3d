/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_determine_movement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:48:15 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/17 23:50:59 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_player_movement(t_data *data)
{
	if (data->keys.d)
		data->player.angle += ROTATION_SPEED;
	if (data->keys.a)
		data->player.angle -= ROTATION_SPEED;
	if (data->keys.up)
	{
		data->player.position.y += MOVE_SPEED * data->player.dir.y;
		data->player.position.x += MOVE_SPEED * data->player.dir.x;
	}
	if (data->keys.down)
	{
		data->player.position.y -= MOVE_SPEED * data->player.dir.y;
		data->player.position.x -= MOVE_SPEED * data->player.dir.x;
	}
	if (data->keys.right)
	{
		data->player.position.x += MOVE_SPEED * -data->player.dir.y;
		data->player.position.y += MOVE_SPEED * data->player.dir.x;
	}
	if (data->keys.left)
	{
		data->player.position.x += MOVE_SPEED * data->player.dir.y;
		data->player.position.y += MOVE_SPEED * -data->player.dir.x;
	}
	return (0);
}
