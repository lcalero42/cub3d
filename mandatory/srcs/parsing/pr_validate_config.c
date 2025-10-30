/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_validate_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:58:01 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/30 16:32:46 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_config(t_data *data)
{
	int	required_elements;

	required_elements = 6;
	if (data->config_lines < required_elements)
	{
		printf("\033[1;31mError\nExpected %d config elements, got %d\n\033[0m",
			required_elements, data->config_lines);
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
