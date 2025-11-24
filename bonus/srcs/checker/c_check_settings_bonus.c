/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_settings_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:09:32 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/24 17:26:59 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_settings(void)
{
	if (MOVE_SPEED < 0.1f || MOVE_SPEED > 100.0f)
		u_print_error("Wrong move speed (min : 0.1, max 100)");
	if (CROSSHAIR_SIZE < 1 || CROSSHAIR_THICKNESS < 1)
		u_print_error("Wrong crosshair settings");
	if (SENSITIVITY < 0.1f || SENSITIVITY > 100.0f)
		u_print_error("Wrong sensitivity (min : 0.1, max 100)");
	if (RELOAD_TIME_MS < 0.1f || RELOAD_TIME_MS > 10000.0f)
		u_print_error("Wrong reload time (min : 0.1, max 10000)");
	if (RENDER_DISTANCE < 1 || RENDER_DISTANCE > 5000)
		u_print_error("Wrong render distance (min : 1, max 5000)");
	if ((MOVE_SPEED < 0.1f || MOVE_SPEED > 100.0f)
		|| (CROSSHAIR_SIZE < 1 || CROSSHAIR_THICKNESS < 1)
		|| (SENSITIVITY < 0.1f || SENSITIVITY > 100.0f)
		|| (RELOAD_TIME_MS < 0.1f || RELOAD_TIME_MS > 10000.0f)
		|| (RENDER_DISTANCE < 1 || RENDER_DISTANCE > 5000))
		return (0);
	return (1);
}
