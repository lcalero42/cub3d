/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_vector_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:53:43 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/28 14:08:39 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	vec_add(t_vector *v1, t_vector *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
}

static inline void	vec_scale(t_vector *v, double scale)
{
	v->x *= scale;
	v->y *= scale;
}
