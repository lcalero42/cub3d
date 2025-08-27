/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_ft_free_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:54:06 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 16:23:27 by ekeisler         ###   ########.fr       */
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
}
