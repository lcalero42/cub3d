/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_wall_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:19:52 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/14 19:45:04 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		draw_wall_column(t_data *data, int x);
static int		get_wall_pixel(t_data *data, int x, int y, 
					int i, int line_height, int wall_top);
static void		find_visible_pixel(t_data *data, int x, int y,
					t_pixel_data *result);

void	render_walls(t_data *data)
{
	int		x;

	x = 0;
	data->player.pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);
	while (x < WINDOW_WIDTH)
	{
		data->current_ray_index = x;
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
		wall_x = data->player.position.y
			+ perp_dist * data->rays[ray_index].ray_dir.y;
	else
		wall_x = data->player.position.x
			+ perp_dist * data->rays[ray_index].ray_dir.x;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * 64);
	if ((side == 0 && data->rays[ray_index].ray_dir.x > 0)
		|| (side == 1 && data->rays[ray_index].ray_dir.y < 0))
		tex_x = 64 - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_column(t_data *data, int x)
{
	int				y;
	int				fog_alpha;
	t_pixel_data	pix;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		find_visible_pixel(data, x, y, &pix);
		if (pix.found)
		{
			fog_alpha = calculate_fog_alpha(pix.dist);
			if (fog_alpha > 0 && data->render_fog)
				pix.pixel = blend_fog_with_pixel(pix.pixel,
						u_rgb_to_hex(FOG_COLOR_R, FOG_COLOR_G,
							FOG_COLOR_B, 255), fog_alpha);
			put_pixel_to_image(data, x, y, pix.pixel);
		}
		y++;
	}
}

static int	get_wall_pixel(t_data *data, int x, int y, 
	int i, int line_height, int wall_top)
{
	double step;
	
	step = 64.0 / line_height;
	return (get_wall_texture_pixel(data,
		(int)((y - wall_top) * step) & 63, x, i));
}

static void	find_visible_pixel(t_data *data, int x, int y,
	t_pixel_data *result)
{
	int i;
	int wall_bottom;
	int line_height;
	int wall_top;
	int pixel;
	
	result->found = 0;
	i = -1;
	while (++i < data->rays[x].index_hit)
	{
		line_height = (int)(WINDOW_HEIGHT 
			/ data->rays[x].perp_wall_dist_per_hit[i]);
		wall_top = -line_height / 2 + WINDOW_HEIGHT / 2 + (int)data->player.pitch_offset;
		wall_bottom = line_height / 2 + WINDOW_HEIGHT / 2 + (int)data->player.pitch_offset - 1;
		if (y < wall_top || y > wall_bottom)
			continue ;
		pixel = get_wall_pixel(data, x, y, i, line_height, wall_top);
		if (!is_transparent_color(pixel))
			return (result->pixel = pixel,
				result->dist = data->rays[x].perp_wall_dist_per_hit[i],
				result->found = 1, (void)0);
	}
}
