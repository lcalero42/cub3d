/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_enemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:48:01 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/27 17:56:57 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

unsigned int	get_texture_pixel(t_texture_info *texture_info, int x, int y)
{
	int			bytes_per_pixel;
	char		*pixel_addr;
	unsigned char	r, g, b, a;

	bytes_per_pixel = texture_info->bpp / 8;
	pixel_addr = texture_info->addr + y * texture_info->line_len 
		+ x * bytes_per_pixel;
	b = (unsigned char)pixel_addr[0];
	g = (unsigned char)pixel_addr[1];
	r = (unsigned char)pixel_addr[2];
	if (bytes_per_pixel == 4)
		a = (unsigned char)pixel_addr[3];
	else
		a = 255;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

static int	is_transparent_color(unsigned int color)
{
	unsigned char	r, g, b;

	// Extract RGB components
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	
	// Check if it's black (transparent in your case)
	if (color == 0x00FFFFFF)
		return (1);
	return (0);
}

static void	calculate_sprite_bounds(int screen_x, int sprite_height, 
	t_sprite_bounds *bounds)
{
	int	half_width;

	half_width = sprite_height / 2;
	bounds->start_x = screen_x - half_width;
	bounds->end_x = screen_x + half_width;
	bounds->half_width = half_width;
	
	// Clamp to screen boundaries
	if (bounds->start_x < 0)
		bounds->start_x = 0;
	if (bounds->end_x >= WINDOW_WIDTH)
		bounds->end_x = WINDOW_WIDTH - 1;
}

static void	draw_sprite_column(t_data *data, t_sprite_params *params)
{
	int		y;
	int		tex_y;
	unsigned int	color;

	y = params->sprite_top;
	while (y < params->sprite_top + params->sprite_height 
		&& y < WINDOW_HEIGHT)
	{
		if (y < 0)
		{
			y++;
			continue;
		}
		
		// Map y screen coordinate to texture coordinate (0 to 64)
		tex_y = (int)((float)(y - params->sprite_top) * 64 
			/ params->sprite_height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= 64)
			tex_y = 64 - 1;
		
		color = get_texture_pixel(params->tex_info, params->tex_x, tex_y);

		if (!is_transparent_color(color))
			put_pixel_to_image(data, params->x, y, color);
		
		y++;
	}
}

void	draw_sprite_at(t_data *data, t_render *render, int screen_x, 
	int sprite_top, int sprite_height, t_enemy *enemy)
{
	t_sprite_bounds	bounds;
	t_sprite_params	params;
	int				x;

	calculate_sprite_bounds(screen_x, sprite_height, &bounds);
	
	params.tex_info = &render->info;
	params.sprite_top = sprite_top;
	params.sprite_height = sprite_height;
	
	x = bounds.start_x;
	while (x <= bounds.end_x)
	{
		// Map x screen coordinate to texture coordinate (0 to 64)
		if (data->rays[x].hit == 1 && data->rays[x].perp_wall_dist < sqrtf((enemy->position.x - data->player.position.x) * (enemy->position.x - data->player.position.x)  + (enemy->position.y - data->player.position.y)  * (enemy->position.y - data->player.position.y)))
		{
			x++;
			continue ;
		}
		params.tex_x = (int)((float)(x - (screen_x - bounds.half_width)) 
			* 64 / sprite_height);
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

static int	is_enemy_in_fov(float angle_diff, float fov)
{
	return (angle_diff >= -fov / 2 && angle_diff <= fov / 2);
}

static void	calculate_enemy_screen_pos(t_enemy *enemy, t_player *player, 
	t_enemy_render_data *render_data)
{
	float	dx, dy, dist, angle_diff, fov;
	double enemy_angle;

	dx = enemy->position.x - player->position.x;
	dy = enemy->position.y - player->position.y;
	dist = sqrtf(dx * dx + dy * dy);
	
	if (dist < 0.0001f)
	{
		render_data->visible = 0;
		return;
	}
	enemy_angle = atan2f(dy, dx);
	normalize_angle(&enemy_angle);
	normalize_angle(&player->angle);

	angle_diff = enemy_angle - player->angle;
	if (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	else if (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	
	fov = M_PI / 3;
	if (!is_enemy_in_fov(angle_diff, fov))
	{
		render_data->visible = 0;
		return;
	}
	
	render_data->visible = 1;
	render_data->screen_x = (int)((angle_diff + fov / 2) * (WINDOW_WIDTH / fov));
	render_data->sprite_height = (int)(WINDOW_HEIGHT / dist);
	if (render_data->sprite_height > WINDOW_HEIGHT)
		render_data->sprite_height = WINDOW_HEIGHT;
	render_data->sprite_top = (WINDOW_HEIGHT / 2) - (render_data->sprite_height / 2);
}

void	render_enemy(t_data *data)
{
	t_enemy				*enemy;
	t_player			*player;
	t_enemy_render_data	render_data;

	enemy = &data->enemy;
	player = &data->player;
	
	calculate_enemy_screen_pos(enemy, player, &render_data);
	
	if (render_data.visible)
	{
		draw_sprite_at(data, &enemy->render, render_data.screen_x, 
			render_data.sprite_top, render_data.sprite_height, enemy);
	}
}
