/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wall_side_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:19:31 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/03 11:51:54 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_texture_info	get_north_texture_info(t_data *data)
{
	t_texture_info	info;

	info.addr = data->north_wall.info.addr;
	info.bpp = data->north_wall.info.bpp;
	info.line_len = data->north_wall.info.line_len;
	return (info);
}

static t_texture_info	get_south_texture_info(t_data *data)
{
	t_texture_info	info;

	info.addr = data->south_wall.info.addr;
	info.bpp = data->south_wall.info.bpp;
	info.line_len = data->south_wall.info.line_len;
	return (info);
}

static t_texture_info	get_east_texture_info(t_data *data)
{
	t_texture_info	info;

	info.addr = data->east_wall.info.addr;
	info.bpp = data->east_wall.info.bpp;
	info.line_len = data->east_wall.info.line_len;
	return (info);
}

static t_texture_info	get_west_texture_info(t_data *data)
{
	t_texture_info	info;

	info.addr = data->west_wall.info.addr;
	info.bpp = data->west_wall.info.bpp;
	info.line_len = data->west_wall.info.line_len;
	return (info);
}

t_texture_info	get_texture_info_by_side(t_data *data, t_wall_side side)
{
	if (side == NORTH)
		return (get_north_texture_info(data));
	else if (side == SOUTH)
		return (get_south_texture_info(data));
	else if (side == EAST)
		return (get_east_texture_info(data));
	else if (side == WEST)
		return (get_west_texture_info(data));
	else
		return ((t_texture_info){NULL, 0, 0});
}
