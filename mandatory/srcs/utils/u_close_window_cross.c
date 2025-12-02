/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_close_window_cross.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:31:20 by lcalero           #+#    #+#             */
/*   Updated: 2025/12/02 21:40:48 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window_cross(t_data *data)
{
	destroy_images(data);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->game_started)
		mlx_loop_end(data->mlx);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	if (data->grid.grid)
		u_ft_free(data->grid.grid);
	free_paths(data);
	exit(0);
	return (1);
}
