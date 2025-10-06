/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_fog_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:09:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/06 18:54:25 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "cub3d_bonus.h"

static void	process_fog_column(t_data *data, int x);
static void	apply_fog_column(t_data *data, t_fog_params *params);
static void	calculate_wall_bounds(t_data *data, double distance,
				t_wall_bounds *bounds);

void	apply_fog_overlay(t_data *data)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		// if (data->rays[x].index_hit > 1)
		// {
		// 	x++;
		// 	continue ;
		// }
		process_fog_column(data, x);
		x++;
	}
}

static void process_fog_column(t_data *data, int x)
{
    t_ray *ray;
    t_fog_params params;
    t_wall_bounds bounds;
    int drawn_index;
    
    ray = &data->rays[x];
    
    // Use the index that was ACTUALLY DRAWN, not just hit
    drawn_index = data->pixel_render_info[x].index_drawn;
    
    // If nothing was drawn at this column, skip fog
    if (drawn_index < 0)
        return;
    
    // Apply fog based on what was actually rendered
    params.fog_alpha = calculate_fog_alpha(ray->perp_wall_dist_per_hit[drawn_index]);
    
    if (params.fog_alpha > 0)
    {
        calculate_wall_bounds(data, ray->perp_wall_dist_per_hit[drawn_index], &bounds);
        params.x = x;
        params.wall_start = bounds.wall_start;
        params.wall_end = bounds.wall_end;
        params.fog_color = u_rgb_to_hex(FOG_COLOR_R, FOG_COLOR_G, FOG_COLOR_B, 255);
        apply_fog_column(data, &params);
    }
}

static void	apply_fog_column(t_data *data, t_fog_params *params)
{
	int	y;
	int	existing_color;
	int	blended_color;

	y = params->wall_start;
	while (y < params->wall_end)
	{
		existing_color = get_pixel_from_image(data, params->x, y);
		blended_color = blend_fog_with_pixel(existing_color, params->fog_color,
				params->fog_alpha);
		if (!is_transparent_color(existing_color))
			put_pixel_to_image(data, params->x, y, blended_color);
		y++;
	}
}

int	blend_fog_with_pixel(int base_color, int fog_color, int fog_alpha)
{
	t_color	colors;
	double	alpha_factor;

	extract_base_colors(base_color, &colors.base_r, &colors.base_g,
		&colors.base_b);
	extract_fog_colors(fog_color, &colors.fog_r, &colors.fog_g, &colors.fog_b);
	alpha_factor = fog_alpha / 255.0;
	return (blend_colors(&colors, alpha_factor));
}

static void	calculate_wall_bounds(t_data *data, double distance,
				t_wall_bounds *bounds)
{
	int		wall_height;
	double	pitch_offset;

	wall_height = (int)(WINDOW_HEIGHT / distance);
	pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);
	bounds->wall_start = (-wall_height) / 2 + WINDOW_HEIGHT
		/ 2 + (int)pitch_offset;
	bounds->wall_end = wall_height / 2 + WINDOW_HEIGHT / 2 + (int)pitch_offset;
	if (bounds->wall_start < 0)
		bounds->wall_start = 0;
	if (bounds->wall_end >= WINDOW_HEIGHT)
		bounds->wall_end = WINDOW_HEIGHT - 1;
	if (bounds->wall_start >= WINDOW_HEIGHT)
		bounds->wall_start = WINDOW_HEIGHT - 1;
	if (bounds->wall_end < 0)
		bounds->wall_end = 0;
}
