/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_is_config_line_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:21:04 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/03 13:41:10 by ekeisler         ###   ########.fr       */
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
		|| ft_strncmp(trimmed, "EN ", 3) == 0
		|| ft_strncmp(trimmed, "F ", 2) == 0
		|| ft_strncmp(trimmed, "C ", 2) == 0)
		result = 1;
	free(trimmed);
	return (result);
}
