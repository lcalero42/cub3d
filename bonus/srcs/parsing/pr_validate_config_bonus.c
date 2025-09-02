/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_validate_config_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:18:41 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 18:18:44 by lcalero          ###   ########.fr       */
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
