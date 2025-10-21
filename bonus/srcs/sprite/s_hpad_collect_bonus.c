/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_hpad_collect_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:01:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/21 02:39:35 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	add_enemy_sprite(t_data *data, t_generic_sprite *sprites)
{
	double	dx;
	double	dy;

	if (data->enemy.current_health <= 0)
		return (0);
	sprites[0].type = SPRITE_ENEMY;
	sprites[0].position = data->enemy.position;
	sprites[0].data = &data->enemy;
	dx = data->player.position.x - data->enemy.position.x;
	dy = data->player.position.y - data->enemy.position.y;
	sprites[0].distance = sqrt(dx * dx + dy * dy);
	return (1);
}

static void	add_health_pad_sprite(t_data *data, t_generic_sprite *sprites,
	int *count, int i)
{
	double	dx;
	double	dy;

	sprites[*count].type = SPRITE_HEALTH_PAD;
	sprites[*count].position.x = data->health_pad[i].pos.x + 0.5;
	sprites[*count].position.y = data->health_pad[i].pos.y + 0.5;
	sprites[*count].data = &data->health_pad[i];
	dx = data->player.position.x - sprites[*count].position.x;
	dy = data->player.position.y - sprites[*count].position.y;
	sprites[*count].distance = sqrt(dx * dx + dy * dy);
	(*count)++;
}

int	collect_all_sprites(t_data *data, t_generic_sprite *sprites)
{
	int	count;
	int	i;

	count = add_enemy_sprite(data, sprites);
	i = 0;
	while (i < data->health_count)
	{
		if (data->health_pad[i].state == 1)
			add_health_pad_sprite(data, sprites, &count, i);
		i++;
	}
	return (count);
}
