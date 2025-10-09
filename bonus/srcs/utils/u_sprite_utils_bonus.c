/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sprite_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:04:02 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/09 15:16:22 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

static unsigned int	get_texture_pixel(t_texture_info *texture_info,
						int x, int y);

void	calculate_sprite_bounds(int screen_x, int sprite_height,
	t_sprite_bounds *bounds)
{
	int	half_width;

	half_width = sprite_height / 2;
	bounds->start_x = screen_x - half_width;
	bounds->end_x = screen_x + half_width;
	bounds->half_width = half_width;
	if (bounds->start_x < 0)
		bounds->start_x = 0;
	if (bounds->end_x >= WINDOW_WIDTH)
		bounds->end_x = WINDOW_WIDTH - 1;
}

void	draw_sprite_column(t_data *data, t_sprite_params *params)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	y = params->sprite_top;
	while (y < params->sprite_top + params->sprite_height
		&& y < WINDOW_HEIGHT)
	{
		if (y < 0)
		{
			y++;
			continue ;
		}
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

// static int get_door_pixel_at_position(t_data *data, int x, int y, int hit_index)
// {
//     int tex_x;
//     double step;
//     double tex_pos;
//     int tex_y;
//     int line_height;
//     int wall_top;
//     int wall_bottom;
//     double perp_dist;
//     double pitch_offset;
//     t_render *door_texture;
//     t_door *door;
//     int map_x;
//     int map_y;
    
//     perp_dist = data->rays[x].perp_wall_dist_per_hit[hit_index];
//     pitch_offset = data->player.pitch * (WINDOW_HEIGHT * 0.5);
//     line_height = (int)(WINDOW_HEIGHT / perp_dist);
//     wall_top = (-line_height / 2 + WINDOW_HEIGHT / 2) + (int)pitch_offset;
//     wall_bottom = (line_height / 2 + WINDOW_HEIGHT / 2) + (int)pitch_offset - 1;
//     if (y < wall_top || y > wall_bottom)
//         return (-1);
//     tex_x = calculate_texture_x_for_hit(data, x, hit_index);
//     step = 1.0 * 64 / line_height;
//     tex_pos = (y - wall_top) * step;
//     tex_y = (int)tex_pos & (64 - 1);
//     map_x = data->rays[x].hit_map_pos[hit_index].x;
//     map_y = data->rays[x].hit_map_pos[hit_index].y;
//     door = find_door_at(data, map_x, map_y);
//     if (!door)
//         return (-1);
//     if (door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
//         door_texture = &data->door_closed;
//     else
//         door_texture = &data->door_opened;
//     if (tex_x < 0 || tex_x >= 64 || tex_y < 0 || tex_y >= 64)
//         return (-1);
//     return (*(int *)(door_texture->info.addr + 
//             (tex_y * door_texture->info.line_len + 
//              tex_x * (door_texture->info.bpp / 8))));
// }

// int check_wall_occlusion(t_data *data, int x, t_enemy *enemy)
// {
//     int i;
//     int y;
//     double enemy_distance;
//     double dx;
//     double dy;
//     int sprite_top;
//     int sprite_bottom;

//     dx = enemy->position.x - data->player.position.x;
//     dy = enemy->position.y - data->player.position.y;
//     enemy_distance = sqrt(dx * dx + dy * dy);
//     if (x < 0 || x >= WINDOW_WIDTH)
//         return (1);
//     sprite_top = enemy->enemy_data.sprite_top;
//     sprite_bottom = sprite_top + enemy->enemy_data.sprite_height;
//     if (sprite_top < 0)
//         sprite_top = 0;
//     if (sprite_bottom > WINDOW_HEIGHT)
//         sprite_bottom = WINDOW_HEIGHT;
//     i = 0;
//     while (i < data->rays[x].index_hit)
//     {
//         double wall_distance = data->rays[x].perp_wall_dist_per_hit[i];
//         int hit_type = data->rays[x].hit[i];
//         if (wall_distance < enemy_distance)
//         {
//             if (hit_type == 1)
//                 return (1);
//             if (hit_type == 2)
//             {
//                 int sample_count = 0;
//                 int opaque_count = 0;
//                 int step_y = (sprite_bottom - sprite_top) / 5;
//                 if (step_y < 1)
//                     step_y = 1;
//                 for (y = sprite_top; y < sprite_bottom; y += step_y)
//                 {
//                     int pixel = get_door_pixel_at_position(data, x, y, i);
//                     if (pixel != -1)
//                     {
//                         sample_count++;
//                         if (!is_transparent_color(pixel))
//                             opaque_count++;
//                     }
//                 }
//                 if (sample_count > 0 && opaque_count * 2 > sample_count)
//                     return (1);
//             }
//         }
//         i++;
//     }
    
//     return (0);
// }

static unsigned int	get_texture_pixel(t_texture_info *texture_info,
				int x, int y)
{
	int				bytes_per_pixel;
	char			*pixel_addr;
	unsigned char	rgba[4];
	unsigned int	color;

	bytes_per_pixel = texture_info->bpp / 8;
	pixel_addr = texture_info->addr + y * texture_info->line_len
		+ x * bytes_per_pixel;
	rgba[2] = (unsigned char)pixel_addr[0];
	rgba[1] = (unsigned char)pixel_addr[1];
	rgba[0] = (unsigned char)pixel_addr[2];
	if (bytes_per_pixel == 4)
		rgba[3] = (unsigned char)pixel_addr[3];
	else
		rgba[3] = 255;
	color = ((rgba[3] << 24) | (rgba[0] << 16) | (rgba[1] << 8) | rgba[2]);
	return (color);
}

int	is_transparent_color(unsigned int color)
{
	if (color == 0x00FFFFFF)
		return (1);
	return (0);
}
