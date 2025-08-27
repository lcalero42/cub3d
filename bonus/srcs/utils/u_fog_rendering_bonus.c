/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_fog_rendering_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:23:43 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/27 17:57:23 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	calculate_fog_alpha(double distance)
{
	double	ratio;

	if (distance <= FOG_START_DISTANCE)
		return (0);
	if (distance >= FOG_END_DISTANCE)
		return (FOG_MAX_ALPHA);
	ratio = (distance - FOG_START_DISTANCE)
		/ (FOG_END_DISTANCE - FOG_START_DISTANCE);
	return ((int)(ratio * FOG_MAX_ALPHA));
}

void	extract_fog_colors(int fog_color, int *r, int *g, int *b)
{
	*r = (fog_color >> 16) & 0xFF;
	*g = (fog_color >> 8) & 0xFF;
	*b = fog_color & 0xFF;
}
