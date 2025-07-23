/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_close_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:12:24 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/23 15:02:02 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->render_img);
	mlx_destroy_image(data->mlx, data->north_wall.wall_texture_img);
	mlx_destroy_image(data->mlx, data->south_wall.wall_texture_img);
	mlx_destroy_image(data->mlx, data->east_wall.wall_texture_img);
	mlx_destroy_image(data->mlx, data->west_wall.wall_texture_img);
	mlx_destroy_window(data->mlx, data->window);
	mlx_loop_end(data->mlx);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	u_ft_free(data->grid.grid);
	exit(0);
	return (1);
}
