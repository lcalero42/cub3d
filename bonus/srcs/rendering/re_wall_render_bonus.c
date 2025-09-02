/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_wall_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:19:52 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 18:19:54 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	calculate_perp_wall_dist(t_data *data, int x);
static void		calculate_wall_bounds(t_data *data, double perp_wall_dist,
					int *draw_start, int *draw_end);
static int		calculate_texture_x(t_data *data, int x, double perp_wall_dist);
static void		draw_wall_column(t_data *data, int x, int draw_start,
					int draw_end);

void	render_walls(t_data *data)
{
	int		x;
	int		draw_start;
	int		draw_end;
	double	perp_wall_dist;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		data->rays[x].perp_wall_dist = calculate_perp_wall_dist(data, x);
		perp_wall_dist = data->rays[x].perp_wall_dist;
		calculate_wall_bounds(data, perp_wall_dist, &draw_start, &draw_end);
		draw_wall_column(data, x, draw_start, draw_end);
		x++;
	}
}

static double	calculate_perp_wall_dist(t_data *data, int x)
{
	double	perp_wall_dist;

	if (data->rays[x].side == 0)
		perp_wall_dist = data->rays[x].side_dist.x - data->rays[x].delta_dist.x;
	else
		perp_wall_dist = data->rays[x].side_dist.y - data->rays[x].delta_dist.y;
	return (perp_wall_dist);
}

static void	calculate_wall_bounds(t_data *data, double perp_wall_dist,
				int *draw_start, int *draw_end)
{
	int		line_height;
	double	pitch_offset;

	line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
	pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);
	*draw_start = -line_height / 2 + WINDOW_HEIGHT / 2 + (int)pitch_offset;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + WINDOW_HEIGHT / 2 + (int)pitch_offset;
	if (*draw_end >= WINDOW_HEIGHT)
		*draw_end = WINDOW_HEIGHT - 1;
	if (*draw_start >= WINDOW_HEIGHT)
		*draw_start = WINDOW_HEIGHT - 1;
	if (*draw_end < 0)
		*draw_end = 0;
}

static int	calculate_texture_x(t_data *data, int x, double perp_wall_dist)
{
	double	wall_x;
	int		tex_x;

	if (data->rays[x].side == 0)
		wall_x = data->player.position.y
			+ perp_wall_dist * data->rays[x].ray_dir.y;
	else
		wall_x = data->player.position.x
			+ perp_wall_dist * data->rays[x].ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * 64);
	if (data->rays[x].side == 0 && data->rays[x].ray_dir.x > 0)
		tex_x = 64 - tex_x - 1;
	if (data->rays[x].side == 1 && data->rays[x].ray_dir.y < 0)
		tex_x = 64 - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_column(t_data *data, int x, int draw_start,
				int draw_end)
{
	double	perp_wall_dist;
	int		tex_x;
	double	step;
	double	tex_pos;
	double	pitch_offset;
	int		original_wall_center;
	int		y;

	perp_wall_dist = calculate_perp_wall_dist(data, x);
	tex_x = calculate_texture_x(data, x, perp_wall_dist);
	step = 1.0 * 64 / (WINDOW_HEIGHT / perp_wall_dist);
	original_wall_center = WINDOW_HEIGHT / 2;
	pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);
	tex_pos = (draw_start - original_wall_center - (int)pitch_offset
			+ (WINDOW_HEIGHT / perp_wall_dist) / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		put_pixel_to_image(
			data, x, y,
			get_wall_texture_pixel(data, tex_x, (int)tex_pos & (64 - 1), x));
		tex_pos += step;
		y++;
	}
}
