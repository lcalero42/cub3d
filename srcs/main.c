/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/24 15:49:34 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

int	get_pixel_from_image(t_data *data, int x, int y)
{
	char	*pixel_addr;
	int		color;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return (0);
	pixel_addr = data->render_addr
		+ y * data->render_line_len
		+ x * (data->render_bpp / 8);
	color = *(unsigned int *)pixel_addr;
	return (color);
}

int	calculate_fog_alpha(double distance)
{
	if (distance <= FOG_START_DISTANCE)
		return (0);
	if (distance >= FOG_END_DISTANCE)
		return (FOG_MAX_ALPHA);
	return ((int)(((distance - FOG_START_DISTANCE)
			/ (FOG_END_DISTANCE - FOG_START_DISTANCE)) * FOG_MAX_ALPHA));
}

static int	blend_component(int base, int fog, double alpha)
{
	return ((int)(base * (1.0 - alpha) + fog * alpha));
}

int	blend_fog_with_pixel(int base_color, int fog_color, int fog_alpha)
{
	int		base_r;
	int		base_g;
	int		base_b;
	int		fog_r;
	int		fog_g;
	int		fog_b;
	double	alpha_factor;

	base_r = (base_color >> 16) & 0xFF;
	base_g = (base_color >> 8) & 0xFF;
	base_b = base_color & 0xFF;
	fog_r = (fog_color >> 16) & 0xFF;
	fog_g = (fog_color >> 8) & 0xFF;
	fog_b = fog_color & 0xFF;
	alpha_factor = fog_alpha / 255.0;
	return ((blend_component(base_r, fog_r, alpha_factor) << 16)
		| (blend_component(base_g, fog_g, alpha_factor) << 8)
		| blend_component(base_b, fog_b, alpha_factor));
}

static void	apply_fog_column(t_data *data, int x, int wall_end,
		int fog_alpha, int fog_color, int wall_start)
{
	int	y;
	int	existing_color;
	int	blended_color;

	y = wall_start;
	while (y < wall_end)
	{
		existing_color = get_pixel_from_image(data, x, y);
		blended_color = blend_fog_with_pixel(existing_color, fog_color, fog_alpha);
		put_pixel_to_image(data, x, y, blended_color);
		y++;
	}
}

void	apply_fog_overlay(t_data *data)
{
	int		x;
	int		fog_alpha;
	int		fog_color_rgb;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	t_ray	*ray;
	double	distance;

	fog_color_rgb = u_rgb_to_hex(FOG_COLOR_R, FOG_COLOR_G, FOG_COLOR_B, 255);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray = &data->rays[x];
		distance = ray->perp_wall_dist;
		fog_alpha = calculate_fog_alpha(distance);
		if (fog_alpha > 0)
		{
			wall_height = (int)(WINDOW_HEIGHT / distance);
			wall_start = (WINDOW_HEIGHT - wall_height) / 2;
			wall_end = wall_start + wall_height;
			apply_fog_column(data, x, wall_end, fog_alpha, fog_color_rgb, wall_start);
		}
		x++;
	}
}

int key_release_hook(int keycode, t_data *data)
{
	if (keycode == XK_d)
		data->keys.d = 0;
	if (keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_w)
		data->keys.w = 0;
	if (keycode == XK_s)
		data->keys.s = 0;
	if (keycode == XK_Right)
		data->keys.right = 0;
	if (keycode == XK_Left)
		data->keys.left = 0;
	return (0);
}

int key_press_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	if (keycode == XK_f && data->render_fog)
		data->render_fog = 0;
	else if (keycode == XK_f && !data->render_fog)
		data->render_fog = 1;
	if (keycode == XK_d)
		data->keys.d = 1;
	if (keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_w)
		data->keys.w = 1;
	if (keycode == XK_s)
		data->keys.s = 1;
	if (keycode == XK_Right)
		data->keys.right = 1;
	if (keycode == XK_Left)
		data->keys.left = 1;
	return (0);
}

int render_loop(t_data *data)
{	
	update_time(&data->time);
	update_player_movement(data, &data->player, &data->time);
	trace_ray(data, data->player.angle);
	clear_screen(data);
	render_walls(data);
	if (data->render_fog)
		apply_fog_overlay(data);
	mlx_put_image_to_window(data->mlx, data->window, data->render_img, 0, 0);
	return (1);
}

int main(int argc, char **argv)
{
	t_data data;
	
	if (argc != 2)
	{
		printf("error : missing map path\n");
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	data.render_fog = 1;
	if (parse_file(argv[1], &data))
		return (1);
	init_time(&data.time);
	data.mlx = mlx_init();
	find_player_pos(&data);
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	init_walls(&data);
	mlx_hook(data.window, 2, 1L << 0, key_press_hook, &data);
	mlx_hook(data.window, 3, 1L << 1, key_release_hook, &data);
	mlx_hook(data.window, 17, 1L << 17, close_window, &data);
	mlx_loop_hook(data.mlx, render_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	return (0);
}
