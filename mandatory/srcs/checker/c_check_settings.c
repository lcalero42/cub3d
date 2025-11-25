/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:42:55 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/24 17:43:21 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_settings(void)
{
	if (MOVE_SPEED < 0.1f || MOVE_SPEED > 100.0f)
		u_print_error("Wrong move speed (min : 0.1, max 100)");
	if (SENSITIVITY < 0.1f || SENSITIVITY > 100.0f)
		u_print_error("Wrong sensitivity (min : 0.1, max 100)");
	if (RENDER_DISTANCE < 1 || RENDER_DISTANCE > 5000)
		u_print_error("Wrong render distance (min : 1, max 5000)");
	if ((MOVE_SPEED < 0.1f || MOVE_SPEED > 100.0f)
		|| (SENSITIVITY < 0.1f || SENSITIVITY > 100.0f)
		|| (RENDER_DISTANCE < 1 || RENDER_DISTANCE > 5000))
		return (0);
	return (1);
}
