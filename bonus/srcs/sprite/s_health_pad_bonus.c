/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_health_pad_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:56:24 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/16 17:31:57 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_health_sprite_transform(t_data *data,
				t_health_pad *pad, t_sprite_calc *calc);
static void	draw_health_sprite_columns(t_data *data, t_sprite_calc *calc);

void	init_health_pad_system(t_data *data)
{
	int		x;
	int		y;

	data->health_count = 0;
	y = 0;
	while (y < data->grid.height)
	{
		x = 0;
		while (x < data->grid.width && data->grid.grid[y][x])
		{
			if (data->grid.grid[y][x] == 'H')
			{
				data->health_pad[data->health_count].pos.x = x;
				data->health_pad[data->health_count].pos.y = y;
				data->health_pad[data->health_count].state = 1;
				data->health_pad[data->health_count].distance = 0;
				data->health_count++;
			}
			x++;
		}
		y++;
	}
}

void	render_all_health_pads(t_data *data)
{
	int				i;
	t_sprite_calc	calc;
	double			dx;
	double			dy;

	i = 0;
	while (i < data->health_count)
	{
		if (data->health_pad[i].state == 1)
		{
			dx = data->player.position.x - (data->health_pad[i].pos.x + 0.5);
			dy = data->player.position.y - (data->health_pad[i].pos.y + 0.5);
			data->health_pad[i].distance = sqrt(dx * dx + dy * dy);
			calculate_health_sprite_transform(data, &data->health_pad[i],
				&calc);
			if (calc.transform_y > 0.1)
				draw_health_sprite_columns(data, &calc);
		}
		i++;
	}
}

static void	calculate_health_sprite_transform(t_data *data,
	t_health_pad *pad, t_sprite_calc *calc)
{
	double	sprite_x;
	double	sprite_y;

	sprite_x = (pad->pos.x + 0.5) - data->player.position.x;
	sprite_y = (pad->pos.y + 0.5) - data->player.position.y;
	calc->inv_det = 1.0 / (data->player.camera_segment.x * data->player.dir.y
			- data->player.dir.x * data->player.camera_segment.y);
	calc->transform_x = calc->inv_det * (data->player.dir.y * sprite_x
			- data->player.dir.x * sprite_y);
	calc->transform_y = calc->inv_det * (-data->player.camera_segment.y
			* sprite_x + data->player.camera_segment.x * sprite_y);
	if (calc->transform_y <= 0)
		return ;
	calc->screen_x = (int)((WINDOW_WIDTH / 2)
			* (1 + calc->transform_x / calc->transform_y));
	calc->sprite_height = abs((int)(WINDOW_HEIGHT / calc->transform_y));
	calc->sprite_width = abs((int)(WINDOW_HEIGHT / calc->transform_y));
	calc->draw_start_y = -calc->sprite_height / 2 + WINDOW_HEIGHT / 2;
	if (calc->draw_start_y < 0)
		calc->draw_start_y = 0;
	calc->draw_end_y = calc->sprite_height / 2 + WINDOW_HEIGHT / 2;
	if (calc->draw_end_y >= WINDOW_HEIGHT)
		calc->draw_end_y = WINDOW_HEIGHT - 1;
	calc->draw_start_x = -calc->sprite_width / 2 + calc->screen_x;
	if (calc->draw_start_x < 0)
		calc->draw_start_x = 0;
	calc->draw_end_x = calc->sprite_width / 2 + calc->screen_x;
	if (calc->draw_end_x >= WINDOW_WIDTH)
		calc->draw_end_x = WINDOW_WIDTH - 1;
}

static void	draw_health_sprite_columns(t_data *data, t_sprite_calc *calc)
{
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	int				color;
	t_texture_info	*texture;

	texture = &data->health_pad_anim.render_arr[0].info;
	if (!texture->addr)
		return ;
	x = calc->draw_start_x;
	while (x < calc->draw_end_x)
	{
		if (x >= 0 && x < WINDOW_WIDTH)
		{
			tex_x = (int)(256 * (x - (-calc->sprite_width / 2 + calc->screen_x))
					* 64 / calc->sprite_width) / 256;
			y = calc->draw_start_y;
			while (y < calc->draw_end_y)
			{
				tex_y = ((y - WINDOW_HEIGHT / 2 + calc->sprite_height / 2)
						* 64) / calc->sprite_height;
				if (tex_x >= 0 && tex_x < 64 && tex_y >= 0 && tex_y < 64)
				{
					color = *(int *)(texture->addr + tex_y * texture->line_len
							+ tex_x * (texture->bpp / 8));
					if (is_transparent_color(0X00FFFFFF))
						put_pixel_to_image(data, x, y, color);
				}
				y++;
			}
		}
		x++;
	}
}

void	check_health_pickup_collision(t_data *data)
{
	int		i;
	double	dx;
	double	dy;
	double	distance;

	i = 0;
	while (i < data->health_count)
	{
		if (data->health_pad[i].state == 1)
		{
			dx = data->player.position.x - (data->health_pad[i].pos.x + 0.5);
			dy = data->player.position.y - (data->health_pad[i].pos.y + 0.5);
			distance = sqrt(dx * dx + dy * dy);
			if (distance < 0.5)
			{
				data->player.current_health += 25.0;
				if (data->player.current_health > data->player.max_health)
					data->player.current_health = data->player.max_health;
				data->health_pad[i].state = 0;
			}
		}
		i++;
	}
}

t_health_pad	*find_health_at(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->health_count)
	{
		if (data->health_pad[i].pos.x == x && data->health_pad[i].pos.y == y)
			return (&data->health_pad[i]);
		i++;
	}
	return (NULL);
}
