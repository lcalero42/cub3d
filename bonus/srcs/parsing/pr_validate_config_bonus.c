/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_validate_config_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:18:41 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/26 17:28:17 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	validate_config(t_data *data)
{
	int	required_elements;

	required_elements = 7;
	if (data->config_lines < required_elements)
	{
		u_print_error("Expected 7 config elements");
		return (0);
	}
	if (!data->north_wall.texture_path || !data->south_wall.texture_path
		|| !data->west_wall.texture_path || !data->east_wall.texture_path
		|| !data->enemy_render.texture_path)
	{
		u_print_error("Missing texture configuration");
		return (0);
	}
	return (1);
}
