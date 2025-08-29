/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_player_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:52:58 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/29 08:57:55 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	normalize_movement(t_data *data, t_vector *move,
			double *magnitude, double move_speed)
{
	handle_forward_backward(data, move, move_speed);
	handle_strafe(data, move, move_speed);
	*magnitude = sqrt(move->x * move->x + move->y * move->y);
	if (*magnitude > move_speed)
	{
		move->x = (move->x / *magnitude) * move_speed;
		move->y = (move->y / *magnitude) * move_speed;
	}
}
