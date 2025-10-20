/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_hpad_render_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:13:50 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/20 20:05:52 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_tex_x(t_sprite_calc *calc, int x)
{
	return ((int)(256 * (x - (-calc->sprite_width / 2 + calc->screen_x))
		* 64 / calc->sprite_width) / 256);
}

static int	get_tex_y(t_sprite_calc *calc, int y, int sprite_center_y)
{
	return (((y - sprite_center_y + calc->sprite_height / 2)
			* 64) / calc->sprite_height);
}

static void	draw_pixel(t_data *data, t_texture_info *tex, int coords[4])
{
	int	color;

	if (coords[2] < 0 || coords[2] >= 64 || coords[3] < 0 || coords[3] >= 64)
		return ;
	color = *(int *)(tex->addr + coords[3] * tex->line_len
			+ coords[2] * (tex->bpp / 8));
	if (!is_transparent_color(color))
		put_pixel_to_image(data, coords[0], coords[1], color);
}

static void	draw_column(t_data *data, t_sprite_calc *calc,
	t_texture_info *tex, int x)
{
	int	coords[4];
	int	sprite_center_y;

	sprite_center_y = WINDOW_HEIGHT / 2 + (int)data->player.pitch_offset;
	coords[0] = x;
	coords[1] = calc->draw_start_y;
	while (coords[1] < calc->draw_end_y)
	{
		coords[2] = get_tex_x(calc, x);
		coords[3] = get_tex_y(calc, coords[1], sprite_center_y);
		draw_pixel(data, tex, coords);
		coords[1]++;
	}
}

void	render_health_pad_sprite(t_data *data, t_health_pad *pad,
	t_sprite_calc *calc)
{
	int				x;
	t_vector		pad_pos;
	t_texture_info	*texture;

	texture = &data->health_pad_anim.render_arr[
		data->health_pad_anim.index].info;
	if (!texture->addr)
		return ;
	pad_pos.x = pad->pos.x + 0.5;
	pad_pos.y = pad->pos.y + 0.5;
	x = calc->draw_start_x;
	while (x < calc->draw_end_x)
	{
		if (x >= 0 && x < WINDOW_WIDTH
			&& !check_sprite_occlusion(data, x, pad_pos, calc))
			draw_column(data, calc, texture, x);
		x++;
	}
}
