/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_n_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:33:57 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/30 16:48:15 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_only_digit(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]) && !(nptr[i] >= 9
				&& nptr[i] <= 13) && nptr[i] != ' ')
		{
			u_print_error("rgb value must contain only digits or spaces");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_rgb_value(const char *nptr)
{
	int	i;
	int	len;

	if (check_only_digit(nptr))
		return (1);
	i = 0;
	len = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	while (nptr[i])
	{
		i++;
		len++;
	}
	if (len > 3)
	{
		u_print_error("RGB len > 3");
		return (1);
	}
	return (0);
}

int	ft_atoi_n_check(const char *nptr)
{
	size_t	i;
	int		res;
	int		cpt;

	res = 0;
	i = 0;
	cpt = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9' && cpt < 2)
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	if (!check_rgb_value(nptr))
		return (res);
	else
		return (-1);
}
