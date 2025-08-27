/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_get_current_speed_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:33:10 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 16:23:23 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	u_get_current_speed(t_data *data)
{
	if (data->keys.run && data->player.stamina > 0)
		return (MOVE_SPEED * RUN_MULTIPLIER);
	else
		return (MOVE_SPEED);
}
