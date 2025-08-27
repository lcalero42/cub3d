/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_validate_config_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:58:01 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 16:25:12 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	validate_config(t_data *data)
{
	int	required_elements;

	required_elements = 6;
	if (data->config_lines < required_elements)
	{
		printf("Error\nExpected %d config elements, got %d\n",
			required_elements, data->config_lines);
		return (0);
	}
	if (!data->north_wall.texture_path || !data->south_wall.texture_path
		|| !data->west_wall.texture_path || !data->east_wall.texture_path)
	{
		printf("Error\nMissing texture configuration\n");
		return (0);
	}
	return (1);
}
