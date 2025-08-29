/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_texture_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 04:54:05 by ekeisler          #+#    #+#             */
/*   Updated: 2025/08/29 08:56:59 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	parse_texture_path(char **texture_ptr, char *path)
{
	if (*texture_ptr != NULL)
	{
		u_print_error("Duplicate texture definition");
		return (0);
	}
	*texture_ptr = ft_strdup(path);
	if (!*texture_ptr)
		return (0);
	return (1);
}
