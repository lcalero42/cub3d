/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_door_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:59:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/09 18:52:09 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	animation_routine(t_data *data)
{
	static long long	last_anim_time = 0;
	static double		accumulated_time = 0.0;
	long long			current_time;
	double				delta_time;
	double				animation_speed;

	animation_speed = 5.0;
	current_time = get_current_time();
	if (last_anim_time == 0)
	{
		last_anim_time = current_time;
		return ;
	}
	delta_time = (current_time - last_anim_time) / 1000.0;
	accumulated_time += delta_time;
	while (accumulated_time >= 1.0 / animation_speed)
	{
		if (!data->gun.render_arr[data->gun.index + 1].info.addr && data->gun.is_playing)
			data->gun.index = 0;
		else if (data->gun.is_playing)
			data->gun.index++;
		if (!data->shot.render_arr[data->shot.index + 1].info.addr && data->shot.is_playing)
		{
			data->shot.index = 0;
			data->shot.is_playing = 0;
			data->gun.is_playing = 1;
		}
		else if (data->shot.is_playing)
			data->shot.index++;
		accumulated_time -= 1.0 / animation_speed;
	}
	last_anim_time = current_time;
}

void	check_door_distance(t_data *data, int keycode)
{
	int		map_x;
	int		map_y;
	t_ray	middle_ray;

	middle_ray = data->rays[WINDOW_WIDTH / 2];
	map_x = (int)middle_ray.map_pos.x;
	map_y = (int)middle_ray.map_pos.y;
	if (middle_ray.hit == 2 && data->rays[WINDOW_WIDTH
			/ 2].perp_wall_dist < 1.0f && keycode == XK_space)
		data->grid.grid[map_y][map_x] = '0';
}
