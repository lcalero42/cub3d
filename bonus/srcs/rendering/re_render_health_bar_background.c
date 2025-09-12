/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_health_bar_background.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:21:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/12 15:36:50 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_health_bar(t_health_bar *health_bar)
{
	health_bar->current_health = MAX_HEALTH;
	health_bar->max_health = MAX_HEALTH;
	health_bar->x = HEALTH_BAR_X;
	health_bar->y = HEALTH_BAR_Y;
	health_bar->width = HEALTH_BAR_WIDTH;
	health_bar->height = HEALTH_BAR_HEIGHT;
}

static void	draw_border(t_data *data, t_health_bar *health_bar)
{
	int	x;
	int	y;

	y = health_bar->y - 2;
	while (y < health_bar->y + health_bar->height + 2)
	{
		x = health_bar->x - 2;
		while (x < health_bar->x + health_bar->width + 2)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				put_pixel_to_image(data, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

static void	draw_background(t_data *data, t_health_bar *health_bar)
{
	int	x;
	int	y;

	y = health_bar->y;
	while (y < health_bar->y + health_bar->height)
	{
		x = health_bar->x;
		while (x < health_bar->x + health_bar->width)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				put_pixel_to_image(data, x, y, 0x330000);
			x++;
		}
		y++;
	}
}

void	draw_health_bar_background(t_data *data, t_health_bar *health_bar)
{
	draw_border(data, health_bar);
	draw_background(data, health_bar);
}

unsigned int	get_health_color(t_health_bar *health_bar)
{
	if (health_bar->current_health > health_bar->max_health * 0.6)
		return (0x00FF00);
	else if (health_bar->current_health > health_bar->max_health * 0.3)
		return (0xFFFF00);
	else
		return (0xFF0000);
}
