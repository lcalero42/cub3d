/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init_mouse_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:19:07 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/30 14:44:10 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_mouse_control(t_data *data)
{
    if (!data->mlx || !data->window)
    {
        printf("Error: MLX not initialized before mouse setup\n");
        return;
    }
    data->mouse.first_move = 1;
    data->mouse.last_x = 0;
    data->mouse.enabled = 1;
    data->mouse.sensitivity = SENSITIVITY;
}