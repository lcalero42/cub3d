/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_health_pad_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:11:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/20 19:29:13 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
				data->grid.grid[(int)data->health_pad[i].pos.y][(int)data->health_pad[i].pos.x] = '0';
			}
		}
		i++;
	}
}


static void	swap_sprites(t_generic_sprite *a, t_generic_sprite *b)
{
	t_generic_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_sprites_by_distance(t_generic_sprite *sprites, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (sprites[j].distance < sprites[j + 1].distance)
				swap_sprites(&sprites[j], &sprites[j + 1]);
			j++;
		}
		i++;
	}
}

static int	collect_all_sprites(t_data *data, t_generic_sprite *sprites)
{
	int		count;
	int		i;
	double	dx;
	double	dy;

	count = 0;
	if (data->enemy.current_health > 0)
	{
		sprites[count].type = SPRITE_ENEMY;
		sprites[count].position = data->enemy.position;
		sprites[count].data = &data->enemy;
		dx = data->player.position.x - data->enemy.position.x;
		dy = data->player.position.y - data->enemy.position.y;
		sprites[count].distance = sqrt(dx * dx + dy * dy);
		count++;
	}
	i = 0;
	while (i < data->health_count)
	{
		if (data->health_pad[i].state == 1)
		{
			sprites[count].type = SPRITE_HEALTH_PAD;
			sprites[count].position.x = data->health_pad[i].pos.x + 0.5;
			sprites[count].position.y = data->health_pad[i].pos.y + 0.5;
			sprites[count].data = &data->health_pad[i];
			dx = data->player.position.x - sprites[count].position.x;
			dy = data->player.position.y - sprites[count].position.y;
			sprites[count].distance = sqrt(dx * dx + dy * dy);
			count++;
		}
		i++;
	}
	return (count);
}

static void	calculate_sprite_transform(t_data *data, t_generic_sprite *sprite)
{
	double	sprite_x;
	double	sprite_y;
	double	scale;  // ADD THIS

	sprite_x = sprite->position.x - data->player.position.x;
	sprite_y = sprite->position.y - data->player.position.y;
	sprite->calc.inv_det = 1.0 / (data->player.camera_segment.x
			* data->player.dir.y - data->player.dir.x
			* data->player.camera_segment.y);
	sprite->calc.transform_x = sprite->calc.inv_det
		* (data->player.dir.y * sprite_x - data->player.dir.x * sprite_y);
	sprite->calc.transform_y = sprite->calc.inv_det
		* (-data->player.camera_segment.y * sprite_x
			+ data->player.camera_segment.x * sprite_y);
	if (sprite->calc.transform_y <= 0)
		return ;
	sprite->calc.screen_x = (int)((WINDOW_WIDTH / 2)
			* (1 + sprite->calc.transform_x / sprite->calc.transform_y));
	
	// ADD THIS: Scale health pads smaller
	scale = 1.0;
	if (sprite->type == SPRITE_HEALTH_PAD)
		scale = 0.5;  // 50% size (adjust this: 0.3 = 30%, 0.7 = 70%)
	
	sprite->calc.sprite_height = abs((int)(WINDOW_HEIGHT
				/ sprite->calc.transform_y * scale));  // Apply scale
	sprite->calc.sprite_width = abs((int)(WINDOW_HEIGHT
				/ sprite->calc.transform_y * scale));   // Apply scale
	
	sprite->calc.draw_start_y = -sprite->calc.sprite_height / 2
		+ WINDOW_HEIGHT / 2 + (int)data->player.pitch_offset;
	if (sprite->calc.draw_start_y < 0)
		sprite->calc.draw_start_y = 0;
	sprite->calc.draw_end_y = sprite->calc.sprite_height / 2
		+ WINDOW_HEIGHT / 2 + (int)data->player.pitch_offset;
	if (sprite->calc.draw_end_y >= WINDOW_HEIGHT)
		sprite->calc.draw_end_y = WINDOW_HEIGHT - 1;
	sprite->calc.draw_start_x = -sprite->calc.sprite_width / 2
		+ sprite->calc.screen_x;
	if (sprite->calc.draw_start_x < 0)
		sprite->calc.draw_start_x = 0;
	sprite->calc.draw_end_x = sprite->calc.sprite_width / 2
		+ sprite->calc.screen_x;
	if (sprite->calc.draw_end_x >= WINDOW_WIDTH)
		sprite->calc.draw_end_x = WINDOW_WIDTH - 1;
}


static void	render_sprite(t_data *data, t_generic_sprite *sprite)
{
	if (sprite->calc.transform_y <= 0)
		return ;
	if (sprite->type == SPRITE_ENEMY)
		render_enemy_with_health(data, &data->enemy);
	else if (sprite->type == SPRITE_HEALTH_PAD)
		render_health_pad_sprite(data, (t_health_pad *)sprite->data,
			&sprite->calc);
}

void	render_all_sprites(t_data *data)
{
	t_generic_sprite	sprites[MAX_HEALTH_PAD + 1];
	int					sprite_count;
	int					i;

	sprite_count = collect_all_sprites(data, sprites);
	sort_sprites_by_distance(sprites, sprite_count);
	i = 0;
	while (i < sprite_count)
	{
		calculate_sprite_transform(data, &sprites[i]);
		render_sprite(data, &sprites[i]);
		i++;
	}
}
