/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:02:02 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/12 14:51:09 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	key_release_hook(int keycode, t_data *data)
{
	if (keycode == XK_d || keycode == XK_a || keycode == XK_w
		|| keycode == XK_s)
		data->player.is_moving = 0;
	if (keycode == XK_d)
		data->keys.d = 0;
	if (keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_w)
		data->keys.w = 0;
	if (keycode == XK_s)
		data->keys.s = 0;
	if (keycode == XK_Right)
		data->keys.right = 0;
	if (keycode == XK_Left)
		data->keys.left = 0;
	if (keycode == XK_Shift_L)
		data->keys.run = 0;
	return (0);
}

int	key_press_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	handle_move_keys(data, keycode);
	if (keycode == XK_f && data->render_fog)
		data->render_fog = 0;
	else if (keycode == XK_f && !data->render_fog)
		data->render_fog = 1;
	if (keycode == XK_m || keycode == XK_M)
		toggle_mouse_control(data);
	check_door_distance(data, keycode);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 1)
	{
		data->shot.is_playing = 1;
		data->shot.index = 0;
		data->shot.index = 0;
		data->gun.is_playing = 0;
		trace_shot(data);
	}
	return (0);
}
