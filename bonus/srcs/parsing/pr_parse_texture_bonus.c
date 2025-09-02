/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_texture_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/02 17:23:54 by lcalero          ###   ########.fr       */
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
