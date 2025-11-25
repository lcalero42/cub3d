/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_enemy_spawn_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:11:30 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/17 16:17:43 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_enemy_can_spawn(t_data *data)
{
	int	i;
	int	can_spawn_enemy;

	i = 0;
	can_spawn_enemy = 0;
	while (data->grid.grid[i])
	{
		if (ft_strchr(data->grid.grid[i], '0'))
			can_spawn_enemy = 1;
		i++;
	}
	if (!can_spawn_enemy)
	{
		u_print_error("Cannot find a place to spawn enemy");
		close_window(data);
	}
}
