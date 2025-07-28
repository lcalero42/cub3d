/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_delta_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:33:02 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/28 14:16:06 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	calculate_fps(void)
{
	int					fps;
	static int			frame_count = 0;
	static long long	current_time = 0;
	static long long	last_sec_time = 0;

	fps = 0;
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
		fps = frame_count;
		frame_count = 0;
		last_sec_time = current_time;
		printf("fps: %d\n", fps);
	}
}
