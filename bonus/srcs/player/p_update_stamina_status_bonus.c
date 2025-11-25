/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_update_stamina_status_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:56:28 by ekeisler          #+#    #+#             */
/*   Updated: 2025/09/22 13:55:58 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_player_stamina_status(t_data *data)
{
	if (data->player.is_running)
	{
		data->player.stamina -= STAMINA_DRAIN_RATE * data->delta_time;
		if (data->player.stamina <= 0)
		{
			data->keys.run = 0;
			data->player.is_running = 0;
			data->player.stamina = 0;
		}
	}
	else if (!data->player.is_running)
	{
		data->player.stamina += (STAMINA_REGEN_RATE * data->delta_time);
		if (data->player.stamina > MAX_STAMINA)
			data->player.stamina = MAX_STAMINA;
	}
}
