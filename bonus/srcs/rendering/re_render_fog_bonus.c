/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_fog_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:09:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/09 17:29:07 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	blend_fog_with_pixel(int base_color, int fog_color, int fog_alpha)
{
	t_color	colors;
	double	alpha_factor;

	extract_base_colors(base_color, &colors.base_r, &colors.base_g,
		&colors.base_b);
	extract_fog_colors(fog_color, &colors.fog_r, &colors.fog_g, &colors.fog_b);
	alpha_factor = fog_alpha / 255.0;
	return (blend_colors(&colors, alpha_factor));
}
