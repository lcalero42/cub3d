/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_render_sprite_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:13:50 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/20 19:22:17 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:11:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/20 19:11:00 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_health_pad_sprite(t_data *data, t_health_pad *pad,
	t_sprite_calc *calc)
{
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	int				color;
	int				sprite_center_y;
	t_vector		pad_pos;
	t_texture_info	*texture;

	texture = &data->health_pad_anim.render_arr[data->health_pad_anim.index].info;
	if (!texture->addr)
		return ;
	sprite_center_y = WINDOW_HEIGHT / 2 + (int)data->player.pitch_offset;
	pad_pos.x = pad->pos.x + 0.5;
	pad_pos.y = pad->pos.y + 0.5;
	x = calc->draw_start_x;
	while (x < calc->draw_end_x)
	{
		if (x >= 0 && x < WINDOW_WIDTH)
		{
			if (check_sprite_occlusion(data, x, pad_pos, calc))
			{
				x++;
				continue ;
			}
			tex_x = (int)(256 * (x - (-calc->sprite_width / 2
						+ calc->screen_x)) * 64 / calc->sprite_width) / 256;
			y = calc->draw_start_y;
			while (y < calc->draw_end_y)
			{
				tex_y = ((y - sprite_center_y + calc->sprite_height / 2)
						* 64) / calc->sprite_height;
				if (tex_x >= 0 && tex_x < 64 && tex_y >= 0 && tex_y < 64)
				{
					color = *(int *)(texture->addr + tex_y * texture->line_len
							+ tex_x * (texture->bpp / 8));
					if (!is_transparent_color(color))
						put_pixel_to_image(data, x, y, color);
				}
				y++;
			}
		}
		x++;
	}
}

