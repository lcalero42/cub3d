/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_render_enemy_health_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:42:45 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/22 14:40:39 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

static void	normalize_angle(double *angle);
static void	calculate_angle_diff(t_enemy *enemy, t_player *player,
				t_enemy_render_data *render_data);

void	calculate_enemy_screen_pos(t_enemy *enemy, t_player *player,
	t_enemy_render_data *render_data, t_data *data)
{
	float	dx;
	float	dy;
	float	dist;
	float	fov;

	dx = enemy->position.x - player->position.x;
	dy = enemy->position.y - player->position.y;
	player->pitch_offset = player->pitch * (WINDOW_HEIGHT * 0.5);
	dist = sqrtf(dx * dx + dy * dy);
	if (dist <= 2.0f)
		player->current_health -= LIFE_DRAIN_RATE * data->delta_time;
	calculate_angle_diff(enemy, player, render_data);
	fov = M_PI / 3;
	render_data->visible = 1;
	render_data->screen_x = (int)((render_data->angle_diff + fov / 2)
			* (WINDOW_WIDTH / fov));
	render_data->sprite_height = (int)(WINDOW_HEIGHT / dist);
	if (render_data->sprite_height > WINDOW_HEIGHT)
		render_data->sprite_height = WINDOW_HEIGHT;
	render_data->sprite_top = (WINDOW_HEIGHT / 2) - (render_data->sprite_height
			/ 2) + player->pitch_offset;
}

void	calculate_health_bar_position(t_enemy_render_data *r_dt,
	t_enemy_health_bar *health_bar)
{
	int	bar_width;
	int	bar_height;

	bar_width = r_dt->sprite_height / 3;
	bar_height = 8;
	if (bar_width < 20)
		bar_width = 20;
	health_bar->x = r_dt->screen_x - bar_width / 2;
	health_bar->y = r_dt->sprite_top - bar_height - 10;
	health_bar->width = bar_width;
	health_bar->height = bar_height;
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

static void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}
