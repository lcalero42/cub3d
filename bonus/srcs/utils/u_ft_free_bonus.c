/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_ft_free_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:20:48 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/21 04:49:17 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	u_ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (res[i])
			free(res[i]);
		i++;
	}
	if (res)
		free(res);
	res = NULL;
}

void	u_ft_free_doors(t_data *data)
{
	int	y;

	if (!data->door_grid)
		return ;
	y = 0;
	while (y < data->grid.height)
	{
		if (data->door_grid[y])
			free(data->door_grid[y]);
		y++;
	}
	free(data->door_grid);
	data->door_grid = NULL;
}
