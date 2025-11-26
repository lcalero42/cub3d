/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_print_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:59:38 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/26 18:18:59 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	u_print_error(char *msg)
{
	static int	called = 0;

	if (called)
		return ;
	called = 1;
	ft_putstr_fd("\033[1;31mError\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n\033[0m", 2);
}
