/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_sprite_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:04:42 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/28 15:41:07 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static void	draw_sprite_at(t_data *data, t_render *render,
		t_sprite_bounds *bounds, t_enemy *enemy)
{
	t_sprite_params	params;
	int				x;
	int				screen_x;

	params = init_sprite_params(&render->info, bounds->sprite_top,
			bounds->sprite_height);
	x = bounds->start_x;
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

static void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}

static void	calculate_angle_diff(t_enemy *enemy, t_player *player,
		t_enemy_render_data *render_data)
{
	float	dx;
	float	dy;
	double	enemy_angle;
	float	angle_diff;

	dx = enemy->position.x - player->position.x;
	dy = enemy->position.y - player->position.y;
	enemy_angle = atan2f(dy, dx);
	normalize_angle(&enemy_angle);
	normalize_angle(&player->angle);
	angle_diff = enemy_angle - player->angle;
	if (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	else if (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	render_data->angle_diff = angle_diff;
}

static void	calculate_enemy_screen_pos(t_enemy *enemy, t_player *player,
		t_enemy_render_data *render_data)
{
	float	dx;
	float	dy;
	float	dist;
	float	fov;

	dx = enemy->position.x - player->position.x;
	dy = enemy->position.y - player->position.y;
	dist = sqrtf(dx * dx + dy * dy);
	calculate_angle_diff(enemy, player, render_data);
	fov = M_PI / 3;
	if (render_data->angle_diff < -fov / 2 || render_data->angle_diff > fov / 2)
	{
		render_data->visible = 0;
		return ;
	}
	render_data->visible = 1;
	render_data->screen_x = (int)((render_data->angle_diff + fov / 2)
			* (WINDOW_WIDTH / fov));
	render_data->sprite_height = (int)(WINDOW_HEIGHT / dist);
	if (render_data->sprite_height > WINDOW_HEIGHT)
		render_data->sprite_height = WINDOW_HEIGHT;
	render_data->sprite_top = (WINDOW_HEIGHT / 2) - (render_data->sprite_height
			/ 2);
}

void	render_enemy(t_data *data)
{
	t_sprite_bounds	bounds;

	calculate_enemy_screen_pos(&data->enemy, &data->player,
		&data->enemy.enemy_data);
	if (data->enemy.enemy_data.visible)
	{
		calculate_sprite_bounds(data->enemy.enemy_data.screen_x,
			data->enemy.enemy_data.sprite_height, &bounds);
		bounds.sprite_height = data->enemy.enemy_data.sprite_height;
		bounds.sprite_top = data->enemy.enemy_data.sprite_top;
		draw_sprite_at(data, &data->enemy.render, &bounds, &data->enemy);
	}
}
