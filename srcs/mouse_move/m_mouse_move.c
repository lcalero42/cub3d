/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mouse_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:14:46 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/30 14:42:41 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, t_data *data)
{
    int delta_x;
    
    if (!data || !data->mouse.enabled)
        return (0);
    if (data->mouse.first_move)
    {
        data->mouse.last_x = x;
        data->mouse.first_move = 0;
        return (0);
    }
    delta_x = x - data->mouse.last_x;
    if (abs(delta_x) > 100)
        return (0);
    data->player.angle += delta_x * data->mouse.sensitivity * 0.001f;
    while (data->player.angle < 0)
        data->player.angle += 2 * M_PI;
    while (data->player.angle >= 2 * M_PI)
        data->player.angle -= 2 * M_PI;
    data->mouse.last_x = x;
    return (0);
}
