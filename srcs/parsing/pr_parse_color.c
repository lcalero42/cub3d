/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 04:59:55 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/28 14:21:28 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color(char *color_str, t_color *color)
{
	char	**rgb_parts;

	rgb_parts = ft_split(color_str, ',');
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2])
	{
		u_ft_free(rgb_parts);
		return (0);
	}
	color->base_r = ft_atoi(rgb_parts[0]);
	color->base_g = ft_atoi(rgb_parts[1]);
	color->base_b = ft_atoi(rgb_parts[2]);
	if (color->base_r < 0 || color->base_r > 255
		|| color->base_g < 0 || color->base_g > 255
		|| color->base_b < 0 || color->base_b > 255)
	{
		printf("Error: RGB values must be between 0 and 255\n");
		u_ft_free(rgb_parts);
		return (0);
	}
	u_ft_free(rgb_parts);
	return (1);
}
