/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_skip_whitespace_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:58:09 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/18 18:03:46 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	skip_whitespace(char *all_lines, int i)
{
	while (all_lines[i] && (all_lines[i] == ' '
			|| (all_lines[i] >= 7 && all_lines[i] <= 13)))
		i++;
	return (i);
}
