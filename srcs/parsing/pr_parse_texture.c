/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <enzokeisler89@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 04:54:05 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/18 05:10:13 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_texture_path(char **texture_ptr, char *path) 
{
        if (*texture_ptr != NULL)
    {
        printf("Error: Duplicate texture definition\n");
        return (0);
    }
    *texture_ptr = ft_strdup(path);
    if (!*texture_ptr)
        return (0);
    
    return (1);
}