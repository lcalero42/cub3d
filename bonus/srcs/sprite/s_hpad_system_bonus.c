/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_hpad_system_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:11:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/20 20:12:42 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	swap_sprites(t_generic_sprite *a, t_generic_sprite *b)
{
	t_generic_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_sprites_by_distance(t_generic_sprite *sprites, int count)
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
