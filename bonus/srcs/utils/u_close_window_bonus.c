/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_close_window_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:20:34 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/24 16:56:47 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	destroy_images(t_data *data);
static void	destroy_anim_images(t_data *data);
static void	destroy_ui_anim(t_data *data);

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
	if (data->door_grid)
		u_ft_free_doors(data);
	if (data->all_lines)
		u_ft_free(data->all_lines);
	free_paths(data);
	exit(0);
	return (1);
}

void	free_paths(t_data *data)
{
	if (data->north_wall.texture_path)
		free(data->north_wall.texture_path);
	if (data->south_wall.texture_path)
		free(data->south_wall.texture_path);
	if (data->east_wall.texture_path)
		free(data->east_wall.texture_path);
	if (data->west_wall.texture_path)
		free(data->west_wall.texture_path);
	if (data->enemy_render.texture_path)
		free(data->enemy_render.texture_path);
}

static void	destroy_images(t_data *data)
{
	destroy_anim_images(data);
	destroy_ui_anim(data);
	if (data->render_img)
		mlx_destroy_image(data->mlx, data->render_img);
	if (data->north_wall.texture_img)
		mlx_destroy_image(data->mlx, data->north_wall.texture_img);
	if (data->south_wall.texture_img)
		mlx_destroy_image(data->mlx, data->south_wall.texture_img);
	if (data->east_wall.texture_img)
		mlx_destroy_image(data->mlx, data->east_wall.texture_img);
	if (data->west_wall.texture_img)
		mlx_destroy_image(data->mlx, data->west_wall.texture_img);
	if (data->crosshair.texture_img)
		mlx_destroy_image(data->mlx, data->crosshair.texture_img);
	if (data->enemy_render.texture_img)
		mlx_destroy_image(data->mlx, data->enemy_render.texture_img);
	if (data->door_opened.texture_img)
		mlx_destroy_image(data->mlx, data->door_opened.texture_img);
	if (data->door_closed.texture_img)
		mlx_destroy_image(data->mlx, data->door_closed.texture_img);
}

static void	destroy_anim_images(t_data *data)
{
	if (data->health_pad_anim.render_arr[0].texture_img)
	{
		if (data->health_pad_anim.render_arr[0].texture_img)
			mlx_destroy_image(data->mlx,
				data->health_pad_anim.render_arr[0].texture_img);
		if (data->health_pad_anim.render_arr[1].texture_img)
			mlx_destroy_image(data->mlx,
				data->health_pad_anim.render_arr[1].texture_img);
		if (data->health_pad_anim.render_arr[2].texture_img)
			mlx_destroy_image(data->mlx,
				data->health_pad_anim.render_arr[2].texture_img);
	}
	if (data->shot.render_arr[0].texture_img)
	{
		if (data->shot.render_arr[0].texture_img)
			mlx_destroy_image(data->mlx, data->shot.render_arr[0].texture_img);
		if (data->shot.render_arr[1].texture_img)
			mlx_destroy_image(data->mlx, data->shot.render_arr[1].texture_img);
		if (data->shot.render_arr[2].texture_img)
			mlx_destroy_image(data->mlx, data->shot.render_arr[2].texture_img);
	}
}

static void	destroy_ui_anim(t_data *data)
{
	if (data->play_button.texture_img)
		mlx_destroy_image(data->mlx, data->play_button.texture_img);
	if (data->leave_button.texture_img)
		mlx_destroy_image(data->mlx, data->leave_button.texture_img);
	if (data->menu_background.texture_img)
		mlx_destroy_image(data->mlx, data->menu_background.texture_img);
	if (data->game_over_print.texture_img)
		mlx_destroy_image(data->mlx, data->game_over_print.texture_img);
	if (data->you_won_print.texture_img)
		mlx_destroy_image(data->mlx, data->you_won_print.texture_img);
	if (data->gun.render_arr[0].texture_img)
	{
		if (data->gun.render_arr[0].texture_img)
			mlx_destroy_image(data->mlx, data->gun.render_arr[0].texture_img);
		if (data->gun.render_arr[1].texture_img)
			mlx_destroy_image(data->mlx, data->gun.render_arr[1].texture_img);
		if (data->gun.render_arr[2].texture_img)
			mlx_destroy_image(data->mlx, data->gun.render_arr[2].texture_img);
	}
}
