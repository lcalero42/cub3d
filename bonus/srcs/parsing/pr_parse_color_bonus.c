/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_color_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/03 11:51:17 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	parse_color(char *color_str, t_color *color)
{
	char	**rgb_parts;
	char	*trimmed;

	trimmed = ft_strtrim(color_str, "FC");
	rgb_parts = ft_split(trimmed, ',');
	if (!rgb_parts || !rgb_parts[0]
		|| !rgb_parts[1] || !rgb_parts[2] || rgb_parts[3])
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
		u_print_error("RGB values must be between 0 and 255");
		u_ft_free(rgb_parts);
		return (0);
	}
	u_ft_free(rgb_parts);
	free(trimmed);
	return (1);
}
