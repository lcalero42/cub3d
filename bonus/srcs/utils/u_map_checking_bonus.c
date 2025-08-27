/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_map_checking_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:14:06 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/27 16:22:44 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_out_of_bounds(int x, int y, int height, int width)
{
	return (x < 0 || x >= height || y < 0 || y >= width);
}

int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}
