/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_fill_health_bar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:33:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/12 15:34:22 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	validate_health_bar(t_health_bar *health_bar)
{
	if (health_bar->max_health <= 0)
		return (0);
	if (health_bar->width <= 0 || health_bar->height <= 0)
		return (0);
	if (health_bar->current_health < 0)
		health_bar->current_health = 0;
	return (1);
}

static int	calculate_fill_width(t_health_bar *health_bar)
{
	int	fill_width;

	fill_width = (health_bar->current_health * health_bar->width)
		/ health_bar->max_health;
	return (fill_width);
}

static void	draw_health_fill(t_data *data, t_health_bar *health_bar,
	int fill_width, unsigned int color)
{
	int	x;
	int	y;

	y = health_bar->y;
	while (y < health_bar->y + health_bar->height)
	{
		x = health_bar->x;
		while (x < health_bar->x + fill_width)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				put_pixel_to_image(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_health_bar_fill(t_data *data, t_health_bar *health_bar)
{
	int				fill_width;
	unsigned int	color;

	if (!validate_health_bar(health_bar))
		return ;
	fill_width = calculate_fill_width(health_bar);
	color = get_health_color(health_bar);
	draw_health_fill(data, health_bar, fill_width, color);
}

void	render_health_bar(t_data *data, t_health_bar *health_bar)
{
	draw_health_bar_background(data, health_bar);
	draw_health_bar_fill(data, health_bar);
}
