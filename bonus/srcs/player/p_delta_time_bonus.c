/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_delta_time_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:18:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 18:18:59 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <sys/time.h>

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	calculate_fps(t_data *data)
{
	static int			frame_count = 0;
	static long long	current_time = 0;
	static long long	last_sec_time = 0;
	char				*fps;

	frame_count++;
	if (current_time == 0)
	{
		current_time = get_current_time();
		last_sec_time = current_time;
	}
	else
		current_time = get_current_time();
	if (current_time - last_sec_time >= 1000)
	{
		data->fps = frame_count;
		frame_count = 0;
		last_sec_time = current_time;
	}
	if (data->fps == 0)
		return ;
	fps = ft_itoa(data->fps);
	mlx_string_put(data->mlx, data->window,
		WINDOW_WIDTH * 0.95, WINDOW_HEIGHT * 0.05, 0xFFFFFF, fps);
	free(fps);
}
