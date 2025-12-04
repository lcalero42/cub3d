/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_crosshair_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:19:39 by lcalero           #+#    #+#             */
/*   Updated: 2025/12/04 18:15:51 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_crosshair(t_data *data)
{
	int	x;
	int	y;

	x = (WINDOW_WIDTH >> 1) - CROSSHAIR_SIZE;
	while (x <= (WINDOW_WIDTH >> 1) + CROSSHAIR_SIZE)
	{
		y = (WINDOW_HEIGHT >> 1) - (CROSSHAIR_THICKNESS >> 1);
		while (y <= (WINDOW_HEIGHT >> 1) + (CROSSHAIR_THICKNESS >> 1))
		{
			put_pixel_to_image(data, x, y, CROSSHAIR_COLOR);
			y++;
		}
		x++;
	}
	y = (WINDOW_HEIGHT >> 1) - CROSSHAIR_SIZE;
	while (y <= (WINDOW_HEIGHT >> 1) + CROSSHAIR_SIZE)
	{
		x = (WINDOW_WIDTH >> 1) - (CROSSHAIR_THICKNESS >> 1);
		while (x <= (WINDOW_WIDTH >> 1) + (CROSSHAIR_THICKNESS >> 1))
		{
			put_pixel_to_image(data, x, y, CROSSHAIR_COLOR);
			x++;
		}
		y++;
	}
}
