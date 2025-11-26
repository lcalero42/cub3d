/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_validate_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:58:01 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/26 18:05:08 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_config(t_data *data)
{
	int	required_elements;

	required_elements = 6;
	if (data->config_lines < required_elements)
	{
		u_print_error("Expected 6 config elements");
		return (0);
	}
	if (!data->north_wall.texture_path || !data->south_wall.texture_path
		|| !data->west_wall.texture_path || !data->east_wall.texture_path)
	{
		u_print_error("Missing texture configuration");
		return (0);
	}
	return (1);
}
