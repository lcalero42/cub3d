/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 04:59:55 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/10 18:34:45 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color(char *color_str, t_color *color)
{
	char	**rgb_parts;
	char	*trimmed;

	if (color->base_r || color->base_g || color->base_b)
	{
		u_print_error("Duplicate color settings in map");
		return (0);
	}
	trimmed = ft_strtrim(color_str, "FC");
	rgb_parts = ft_split(trimmed, ',');
	if (!rgb_parts || !rgb_parts[0]
		|| !rgb_parts[1] || !rgb_parts[2] || rgb_parts[3])
	{
		u_ft_free(rgb_parts);
		free(trimmed);
		return (0);
	}
	color->base_r = ft_atoi_n_check(rgb_parts[0]);
	color->base_g = ft_atoi_n_check(rgb_parts[1]);
	color->base_b = ft_atoi_n_check(rgb_parts[2]);
	if (color->base_r < 0 || color->base_r > 255
		|| color->base_g < 0 || color->base_g > 255
		|| color->base_b < 0 || color->base_b > 255)
	{
		u_ft_free(rgb_parts);
		free(trimmed);
		return (0);
	}
	u_ft_free(rgb_parts);
	free(trimmed);
	return (1);
}
