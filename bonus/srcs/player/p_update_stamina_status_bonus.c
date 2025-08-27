/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_update_stamina_status_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:56:28 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 16:24:48 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_player_stamina_status(t_data *data, double delta_time)
{
	if (data->player.is_moving)
	{
		if (data->player.is_running && data->player.is_moving)
		{
			data->player.stamina -= STAMINA_DRAIN_RATE * delta_time;
			if (data->player.stamina <= 0)
			{
				data->keys.run = 0;
				data->player.stamina = 0;
			}
		}
		else if (!data->player.is_running)
		{
			data->player.stamina += STAMINA_REGEN_RATE * delta_time;
			if (data->player.stamina > MAX_STAMINA)
				data->player.stamina = MAX_STAMINA;
		}
	}
}
