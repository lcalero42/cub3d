/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 04:59:55 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/19 12:47:02 by ekeisler         ###   ########.fr       */
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
	color->red = ft_atoi(rgb_parts[0]);
	color->green = ft_atoi(rgb_parts[1]);
	color->blue = ft_atoi(rgb_parts[2]);
	if (color->red < 0 || color->red > 255
		|| color->green < 0 || color->green > 255
		|| color->blue < 0 || color->blue > 255)
	{
		printf("Error: RGB values must be between 0 and 255\n");
		u_ft_free(rgb_parts);
		return (0);
	}
	u_ft_free(rgb_parts);
	return (1);
}
