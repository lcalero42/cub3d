/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_stamina_bar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:41:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/12 18:18:44 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	validate_health_bar(t_health_bar *health_bar, t_data *data)
{
	if (MAX_STAMINA <= 0)
		return (0);
	if (health_bar->width <= 0 || health_bar->height <= 0)
		return (0);
	if (data->player.stamina < 0)
		data->player.stamina = 0;
	return (1);
}

static int	calculate_fill_width(t_health_bar *health_bar, t_data *data)
{
	int	fill_width;

	fill_width = (data->player.stamina * health_bar->width)
		/ MAX_STAMINA;
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

void	draw_stamina_bar_fill(t_data *data, t_health_bar *health_bar)
{
	int				fill_width;
	unsigned int	color;

	if (!validate_health_bar(health_bar, data))
		return ;
	fill_width = calculate_fill_width(health_bar, data);
	color = 0xFFFF00;
	draw_health_fill(data, health_bar, fill_width, color);
}

void	render_stamina(t_data *data, t_health_bar *bar)
{
	bar->x = HEALTH_BAR_X;
	bar->y = HEALTH_BAR_Y * 1.6;
	bar->width = HEALTH_BAR_WIDTH;
	bar->height = HEALTH_BAR_HEIGHT / 2;
	draw_health_bar_background(data, bar);
	draw_stamina_bar_fill(data, bar);
}
