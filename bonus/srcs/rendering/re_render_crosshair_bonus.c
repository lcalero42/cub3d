/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_crosshair_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/02 17:27:06 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d_bonus.h"

void	render_crosshair(t_data *data)
{
	int	x;
	int	y;

	x = WINDOW_WIDTH / 2 - CROSSHAIR_SIZE;
	while (x <= WINDOW_WIDTH / 2 + CROSSHAIR_SIZE)
	{
		y = WINDOW_HEIGHT / 2 - CROSSHAIR_THICKNESS / 2;
		while (y <= WINDOW_HEIGHT / 2 + CROSSHAIR_THICKNESS / 2)
		{
			put_pixel_to_image(data, x, y, CROSSHAIR_COLOR);
			y++;
		}
		x++;
	}
	y = WINDOW_HEIGHT / 2 - CROSSHAIR_SIZE;
	while (y <= WINDOW_HEIGHT / 2 + CROSSHAIR_SIZE)
	{
		x = WINDOW_WIDTH / 2 - CROSSHAIR_THICKNESS / 2;
		while (x <= WINDOW_WIDTH / 2 + CROSSHAIR_THICKNESS / 2)
		{
			put_pixel_to_image(data, x, y, CROSSHAIR_COLOR);
			x++;
		}
		y++;
	}
}
