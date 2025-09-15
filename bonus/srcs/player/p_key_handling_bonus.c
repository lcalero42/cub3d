/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_key_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:56:47 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/11 13:59:02 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_move_keys(t_data *data, int keycode)
{
	if (keycode == XK_d || keycode == XK_a || keycode == XK_w
		|| keycode == XK_s)
		data->player.is_moving = 1;
	if (keycode == XK_Shift_L)
		data->keys.run = 1;
	if (keycode == XK_d)
		data->keys.d = 1;
	if (keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_w)
		data->keys.w = 1;
	if (keycode == XK_s)
		data->keys.s = 1;
	if (keycode == XK_Right)
		data->keys.right = 1;
	if (keycode == XK_Left)
		data->keys.left = 1;
}
