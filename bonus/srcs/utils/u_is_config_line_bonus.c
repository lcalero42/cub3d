/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_is_config_line_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:12:43 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/27 16:22:53 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	u_is_config_line(char *line)
{
	char	*trimmed;
	int		result;

	result = 0;
	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0
		|| ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0
		|| ft_strncmp(trimmed, "EA ", 3) == 0
		|| ft_strncmp(trimmed, "F ", 2) == 0
		|| ft_strncmp(trimmed, "C ", 2) == 0)
		result = 1;
	free(trimmed);
	return (result);
}
