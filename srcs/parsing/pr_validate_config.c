/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_validate_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:58:01 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/19 12:44:46 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_config(t_data *data)
{
	int	required_elements;

	required_elements = 6;
	if (data->config_lines < required_elements)
	{
		printf("Error: Expected %d config elements, got %d\n",
			required_elements, data->config_lines);
		return (0);
	}
	if (!data->north_wall.info.addr || !data->south_wall.info.addr
		|| !data->west_wall.info.addr || !data->east_wall.info.addr)
	{
		printf("Error: Missing texture configuration\n");
		return (0);
	}
	return (1);
}
