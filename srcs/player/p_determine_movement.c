/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_determine_movement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:48:15 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/17 19:08:53 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	determine_movement(int keycode, t_data *data)
{
	if (keycode == XK_d)
		data->player.angle += ROTATION_SPEED;
	if (keycode == XK_a)
		data->player.angle -= ROTATION_SPEED;
	if (keycode == XK_Up)
	{
		data->player.position.y += MOVE_SPEED * data->player.dir.y;
		data->player.position.x += MOVE_SPEED * data->player.dir.x;
	}
	if (keycode == XK_Down)
	{
		data->player.position.y -= MOVE_SPEED * data->player.dir.y;
		data->player.position.x -= MOVE_SPEED * data->player.dir.x;
	}
	if (keycode == XK_Right)
	{
		data->player.position.x += MOVE_SPEED * -data->player.dir.y;
		data->player.position.y += MOVE_SPEED * data->player.dir.x;
	}
	if (keycode == XK_Left)
	{
		data->player.position.x += MOVE_SPEED * data->player.dir.y;
		data->player.position.y += MOVE_SPEED * -data->player.dir.x;
	}
	return (0);
}
