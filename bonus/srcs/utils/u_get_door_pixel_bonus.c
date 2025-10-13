/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_get_door_pixel_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:26:18 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/12 21:35:31 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_wall_bounds(t_data *data,
	int y, int hit_index, t_wall_calc *calc)
{
	double	perp_dist;
	double	pitch_offset;
	double	step;
	double	tex_pos;
	int		x;

	x = data->current_ray_index;
	perp_dist = data->rays[x].perp_wall_dist_per_hit[hit_index];
	pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);
	calc->line_height = (int)(WINDOW_HEIGHT / perp_dist);
	calc->wall_top = (-calc->line_height / 2 + WINDOW_HEIGHT / 2);
	calc->wall_top += (int)pitch_offset;
	calc->wall_bottom = (calc->line_height / 2 + WINDOW_HEIGHT / 2);
	calc->wall_bottom += (int)pitch_offset - 1;
	step = 1.0 * 64 / calc->line_height;
	tex_pos = (y - calc->wall_top) * step;
	calc->tex_y = (int)tex_pos & (64 - 1);
}

static int	get_texture_pixel(t_texture_info *tex_info, int tex_x, int tex_y)
{
	char	*pixel_addr;

	if (tex_x < 0 || tex_x >= 64 || tex_y < 0 || tex_y >= 64)
		return (-1);
	pixel_addr = tex_info->addr + (tex_y * tex_info->line_len
			+ tex_x * (tex_info->bpp / 8));
	return (*(int *)pixel_addr);
}

int	get_door_pixel_at_position(t_data *data, int x,
	int y, int hit_index)
{
	t_wall_calc		calc;
	t_texture_info	tex_info;
	t_door			*door;
	int				tex_x;

	calculate_wall_bounds(data, y, hit_index, &calc);
	if (y < calc.wall_top || y > calc.wall_bottom)
		return (-1);
	tex_x = calculate_texture_x_for_hit(data, x, hit_index);
	door = find_door_at(data, data->rays[x].hit_map_pos[hit_index].x,
			data->rays[x].hit_map_pos[hit_index].y);
	if (!door)
		return (-1);
	tex_info = get_door_texture(data, door);
	return (get_texture_pixel(&tex_info, tex_x, calc.tex_y));
}
