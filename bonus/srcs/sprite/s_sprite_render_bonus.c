/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_sprite_render_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:04:42 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/08 17:21:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

static void	draw_enemy_health_background(t_data *data,
				t_enemy_health_bar *health_bar);
static void	draw_sprite_at(t_data *data, t_render *render,
				t_sprite_bounds *bounds, t_enemy *enemy);
static void	render_enemy_health_bar(t_data *data, t_enemy *enemy,
				t_enemy_render_data *render_data);
static void	draw_enemy_health_fill(t_data *data, t_enemy_health_bar *health_bar,
				t_enemy *enemy);

void	render_enemy_with_health(t_data *data, t_enemy *enemy)
{
	t_sprite_bounds		bounds;

	calculate_enemy_screen_pos(enemy, &data->player, &enemy->enemy_data);
	if (enemy->enemy_data.visible)
	{
		calculate_sprite_bounds(data->enemy.enemy_data.screen_x,
			data->enemy.enemy_data.sprite_height, &bounds);
		bounds.sprite_height = data->enemy.enemy_data.sprite_height;
		bounds.sprite_top = data->enemy.enemy_data.sprite_top;
		draw_sprite_at(data, &data->enemy.render, &bounds, &data->enemy);
		render_enemy_health_bar(data, enemy, &enemy->enemy_data);
	}
}

static void	draw_sprite_at(t_data *data, t_render *render,
		t_sprite_bounds *bounds, t_enemy *enemy)
{
	t_sprite_params	params;
	int				x;
	int				screen_x;

	params = init_sprite_params(&render->info, bounds->sprite_top,
			bounds->sprite_height);
	x = bounds->start_x - data->player.pitch;
	screen_x = enemy->enemy_data.screen_x;
	while (x <= bounds->end_x)
	{
		if (check_wall_occlusion(data, x, enemy))
		{
			x++;
			continue ;
		}
		params.tex_x = (int)((float)((x - (screen_x - bounds->half_width)) * 64)
				/ bounds->sprite_height);
		if (params.tex_x < 0)
			params.tex_x = 0;
		if (params.tex_x >= 64)
			params.tex_x = 64 - 1;
		params.x = x;
		draw_sprite_column(data, &params);
		x++;
	}
}

static void	render_enemy_health_bar(t_data *data, t_enemy *enemy,
	t_enemy_render_data *render_data)
{
	t_enemy_health_bar	health_bar;

	if (!render_data->visible || enemy->current_health <= 0)
		return ;
	calculate_health_bar_position(render_data, &health_bar);
	if (health_bar.x + health_bar.width < 0 || health_bar.x >= WINDOW_WIDTH)
		return ;
	if (health_bar.y + health_bar.height < 0 || health_bar.y >= WINDOW_HEIGHT)
		return ;
	if (check_wall_occlusion(data, health_bar.x, enemy))
		return ;
	draw_enemy_health_background(data, &health_bar);
	draw_enemy_health_fill(data, &health_bar, enemy);
}

static void	draw_enemy_health_background(t_data *data,
	t_enemy_health_bar *health_bar)
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
				put_pixel_to_image(data, x, y, 0x440000);
			x++;
		}
		y++;
	}
}

static void	draw_enemy_health_fill(t_data *data, t_enemy_health_bar *health_bar,
	t_enemy *enemy)
{
	int	x;
	int	y;
	int	fill_width;

	if (enemy->max_health <= 0)
		return ;
	fill_width = (enemy->current_health * health_bar->width)
		/ enemy->max_health;
	y = health_bar->y;
	while (y < health_bar->y + health_bar->height)
	{
		x = health_bar->x;
		while (x < health_bar->x + fill_width)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				put_pixel_to_image(data, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}
