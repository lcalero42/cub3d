/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 04:59:55 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/25 15:38:11 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	extract_rgb_values(char **rgb_parts, t_color *color);
static int	validate_color_range(t_color *color);
static int	validate_and_extract(char **rgb_parts, t_color *color);

static int	validate_and_extract(char **rgb_parts, t_color *color)
{
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1]
		|| !rgb_parts[2] || rgb_parts[3])
		return (0);
	extract_rgb_values(rgb_parts, color);
	return (1);
}

static int	validate_color_range(t_color *color)
{
	if (color->base_r < 0 || color->base_r > 255)
		return (0);
	if (color->base_g < 0 || color->base_g > 255)
		return (0);
	if (color->base_b < 0 || color->base_b > 255)
		return (0);
	return (1);
}

static void	extract_rgb_values(char **rgb_parts, t_color *color)
{
	color->base_r = ft_atoi_n_check(rgb_parts[0]);
	color->base_g = ft_atoi_n_check(rgb_parts[1]);
	color->base_b = ft_atoi_n_check(rgb_parts[2]);
}

int	parse_color(char *color_str, t_color *color)
{
	char	**rgb_parts;
	char	*trimmed;

	if (color->base_r || color->base_g || color->base_b)
		return (0);
	trimmed = ft_strtrim(color_str, "FC");
	if (!trimmed)
		return (0);
	rgb_parts = ft_split(trimmed, ',');
	if (!rgb_parts)
	{
		free(trimmed);
		return (0);
	}
	if (!validate_and_extract(rgb_parts, color)
		|| !validate_color_range(color) || !check_comas(trimmed))
	{
		u_ft_free(rgb_parts);
		free(trimmed);
		return (0);
	}
	u_ft_free(rgb_parts);
	free(trimmed);
	return (1);
}
