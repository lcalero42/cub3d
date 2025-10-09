/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_wall_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:19:52 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/08 17:41:37 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		draw_wall_column(t_data *data, int x);

void	render_walls(t_data *data)
{
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		draw_wall_column(data, x);
		x++;
	}
}

int	calculate_texture_x_for_hit(t_data *data, int ray_index, int hit_index)
{
	double	wall_x;
	int		tex_x;
	double	perp_dist;
	int		side;

	perp_dist = data->rays[ray_index].perp_wall_dist_per_hit[hit_index];
	side = data->rays[ray_index].side_per_hit[hit_index];
	if (side == 0)
		wall_x = data->player.position.y + perp_dist * data->rays[ray_index].ray_dir.y;
	else
		wall_x = data->player.position.x + perp_dist * data->rays[ray_index].ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * 64);
	if ((side == 0 && data->rays[ray_index].ray_dir.x > 0)
		|| (side == 1 && data->rays[ray_index].ray_dir.y < 0))
		tex_x = 64 - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_column(t_data *data, int x)
{
	int y;
	int i;
	double pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);

	for (y = 0; y < WINDOW_HEIGHT; y++)
	{
		int final_pixel = 0;
		int found_pixel = 0;
		double drawn_distance = 0;
		
		for (i = 0; i < data->rays[x].index_hit; i++)
		{
			double perp_dist = data->rays[x].perp_wall_dist_per_hit[i];
			int line_height = (int)(WINDOW_HEIGHT / perp_dist);
			int wall_top = (-line_height / 2 + WINDOW_HEIGHT / 2) + (int)pitch_offset;
			int wall_bottom = (line_height / 2 + WINDOW_HEIGHT / 2) + (int)pitch_offset - 1;

			if (y < wall_top || y > wall_bottom)
				continue;

			int tex_x = calculate_texture_x_for_hit(data, x, i);
			double step = 1.0 * 64 / line_height;
			double tex_pos = (y - wall_top) * step;
			int pixel = get_wall_texture_pixel(data, tex_x, (int)tex_pos & (64 - 1), x, i);
			
			if (!is_transparent_color(pixel))
			{
				final_pixel = pixel;
				found_pixel = 1;
				drawn_distance = perp_dist;
				break;
			}
		}

		if (found_pixel)
		{
			int fog_alpha = calculate_fog_alpha(drawn_distance);
			if (fog_alpha > 0 && data->render_fog)
			{
				int fog_color = u_rgb_to_hex(FOG_COLOR_R, FOG_COLOR_G, FOG_COLOR_B, 255);
				final_pixel = blend_fog_with_pixel(final_pixel, fog_color, fog_alpha);
			}
			put_pixel_to_image(data, x, y, final_pixel);
		}
	}
}
