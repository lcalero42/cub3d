/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_update_animations_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:18:30 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/20 20:25:47 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_gun_indexes(t_data *data, double *acc_time,
				double anim_speed);
static void	update_hpad_indexes(t_data *data, double *acc_hpad_time,
				double hpad_speed);

void	animation_routine(t_data *data)
{
	static double	accumulated_time = 0.0;
	static double	accumulated_hpad_time = 0.0;
	double			animation_speed;
	double			hpad_animation_speed;

	animation_speed = 10.0;
	hpad_animation_speed = 3.0;
	accumulated_time += data->delta_time;
	accumulated_hpad_time += data->delta_time;
	while (accumulated_time >= 1.0 / animation_speed)
		update_gun_indexes(data, &accumulated_time, animation_speed);
	while (accumulated_hpad_time >= 1.0 / hpad_animation_speed)
		update_hpad_indexes(data, &accumulated_hpad_time, hpad_animation_speed);
}

static void	update_gun_indexes(t_data *data, double *acc_time,
	double anim_speed)
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

static void	update_hpad_indexes(t_data *data, double *acc_hpad_time,
	double hpad_speed)
{
	if (!data->health_pad_anim.render_arr[data->health_pad_anim.index
			+ 1].info.addr)
		data->health_pad_anim.index = 0;
	else
		data->health_pad_anim.index++;
	*acc_hpad_time -= 1.0 / hpad_speed;
}
