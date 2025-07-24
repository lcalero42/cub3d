/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_delta_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:33:02 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/24 15:15:46 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void init_time(t_time *time)
{
	time->frame_count = 0;
	time->target_fps = 200.0;
	time->delta_time = 1.0 / time->target_fps;
	time->last_frame_time = 0.0;
}

void update_time(t_time *time)
{
	time->frame_count++;
	time->delta_time = 1.0 / time->target_fps;
}
