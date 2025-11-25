/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_skip_whitespace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:58:09 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/18 17:59:28 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_whitespace(char *all_lines, int i)
{
	while (all_lines[i] && (all_lines[i] == ' '
			|| (all_lines[i] >= 7 && all_lines[i] <= 13)))
		i++;
	return (i);
}
