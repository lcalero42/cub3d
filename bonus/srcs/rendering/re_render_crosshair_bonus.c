/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_crosshair_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:19:39 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/03 11:51:57 by ekeisler         ###   ########.fr       */
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
