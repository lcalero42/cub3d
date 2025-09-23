/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_update_animations_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:18:30 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/22 13:57:36 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_indexes(t_data *data, double *acc_time, double anim_speed);

void	animation_routine(t_data *data)
{
	static double		accumulated_time = 0.0;
	double				animation_speed;

	animation_speed = 10.0;
	accumulated_time += data->delta_time;
	while (accumulated_time >= 1.0 / animation_speed)
		update_indexes(data, &accumulated_time, animation_speed);
}

static void	update_indexes(t_data *data, double *acc_time, double anim_speed)
{
	if (!data->gun.render_arr[data->gun.index + 1].info.addr
		&& data->gun.is_playing)
		data->gun.index = 0;
	else if (data->gun.is_playing)
		data->gun.index++;
	if (!data->shot.render_arr[data->shot.index + 1].info.addr
		&& data->shot.is_playing)
	{
		data->shot.index = 0;
		data->shot.is_playing = 0;
		data->gun.is_playing = 1;
	}
	else if (data->shot.is_playing)
		data->shot.index++;
	*acc_time -= 1.0 / anim_speed;
}
