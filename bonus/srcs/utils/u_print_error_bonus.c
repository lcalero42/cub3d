/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_print_error_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:21:19 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/30 16:35:06 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	u_print_error(char *msg)
{
	ft_putstr_fd("\033[1;31mError\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n\033[0m", 2);
}
