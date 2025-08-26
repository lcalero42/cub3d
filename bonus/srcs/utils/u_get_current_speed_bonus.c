/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_get_current_speed_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:33:10 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/26 17:02:36 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double u_get_current_speed(t_data *data)
{
	if (data->player.is_running)
		return (MOVE_SPEED * RUN_MULTIPLIER);
	else
		return (MOVE_SPEED);
}
