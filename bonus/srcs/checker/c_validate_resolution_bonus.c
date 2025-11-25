/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_validate_resolution_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:56:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/30 16:37:58 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	validate_aspect_ratio_resolution(void);

void	validate_window_size(void)
{
	if (WINDOW_WIDTH < MIN_WIDTH || WINDOW_WIDTH > MAX_WIDTH)
	{
		u_print_error("WINDOW_WIDTH must be between ");
		ft_putnbr_fd(MIN_WIDTH, 2);
		ft_putstr_fd(" and ", 2);
		ft_putnbr_fd(MAX_WIDTH, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	if (WINDOW_HEIGHT < MIN_HEIGHT || WINDOW_HEIGHT > MAX_HEIGHT)
	{
		u_print_error("Error: WINDOW_HEIGHT must be between ");
		ft_putnbr_fd(MIN_HEIGHT, 2);
		ft_putstr_fd(" and ", 2);
		ft_putnbr_fd(MAX_HEIGHT, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	validate_aspect_ratio_resolution();
}

static void	validate_aspect_ratio_resolution(void)
{
	if (WINDOW_WIDTH * 9 != WINDOW_HEIGHT * 16)
	{
		u_print_error("Resolution must be 16:9 ratio\n");
		ft_putstr_fd("Valid 16:9 resolutions:\n", 2);
		ft_putstr_fd("  640x360, 854x480, 1280x720\n", 2);
		ft_putstr_fd("  1600x900, 1920x1080\n", 2);
		exit(1);
	}
	if (WINDOW_WIDTH < 640 || WINDOW_WIDTH > 1920)
	{
		u_print_error("Width must be 640-1920\n");
		exit(1);
	}
	if (WINDOW_HEIGHT < 360 || WINDOW_HEIGHT > 1080)
	{
		u_print_error("Height must be 360-1080\n");
		exit(1);
	}
}
