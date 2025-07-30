/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_close_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:12:24 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/30 15:08:43 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_images(t_data *data);
static void	free_paths(t_data *data);

int	close_window(t_data *data)
{
	if (data->mouse.enabled)
		toggle_mouse_control(data);
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

static void	free_paths(t_data *data)
{
	if (data->north_wall.texture_path)
		free(data->north_wall.texture_path);
	if (data->south_wall.texture_path)
		free(data->south_wall.texture_path);
	if (data->east_wall.texture_path)
		free(data->east_wall.texture_path);
	if (data->west_wall.texture_path)
		free(data->west_wall.texture_path);
}

static void	destroy_images(t_data *data)
{
	if (data->render_img)
		mlx_destroy_image(data->mlx, data->render_img);
	if (data->north_wall.wall_texture_img)
		mlx_destroy_image(data->mlx, data->north_wall.wall_texture_img);
	if (data->south_wall.wall_texture_img)
		mlx_destroy_image(data->mlx, data->south_wall.wall_texture_img);
	if (data->east_wall.wall_texture_img)
		mlx_destroy_image(data->mlx, data->east_wall.wall_texture_img);
	if (data->west_wall.wall_texture_img)
		mlx_destroy_image(data->mlx, data->west_wall.wall_texture_img);
}
