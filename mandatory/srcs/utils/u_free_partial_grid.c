/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_free_partial_grid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:52:44 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/26 17:32:49 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_grid_partial(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(data->grid.grid[i]);
		i++;
	}
	free(data->grid.grid);
	data->grid.grid = NULL;
}
