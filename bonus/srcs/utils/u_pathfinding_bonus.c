/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_pathfinding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:34:56 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 16:19:56 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_astar_data(t_data *data, t_astar_data *astar, t_pos start,
	t_pos goal)
{
	astar->width = data->grid.width;
	astar->height = data->grid.height;
	astar->node_count = 1;
	astar->nodes[0].pos = start;
	astar->nodes[0].g_cost = 0;
	astar->nodes[0].h_cost = heuristic(start, goal);
	astar->nodes[0].f_cost = astar->nodes[0].g_cost + astar->nodes[0].h_cost;
	astar->nodes[0].parent = NULL;
	astar->nodes[0].open = 1;
	astar->nodes[0].closed = 0;
}

int	find_lowest_f_cost(t_astar_data *astar)
{
	int	lowest;
	int	i;

	lowest = -1;
	i = 0;
	while (i < astar->node_count)
	{
		if (astar->nodes[i].open && (lowest == -1
				|| astar->nodes[i].f_cost < astar->nodes[lowest].f_cost))
			lowest = i;
		i++;
	}
	return (lowest);
}

int	reconstruct_path(t_astar_node *goal_node, t_pos *out_path,
	int max_len)
{
	t_astar_node	*trace;
	int				path_len;
	int				i;
	t_pos			tmp;

	path_len = 0;
	trace = goal_node;
	while (trace && path_len < max_len)
	{
		out_path[path_len++] = trace->pos;
		trace = trace->parent;
	}
	i = 0;
	while (i < path_len / 2)
	{
		tmp = out_path[i];
		out_path[i] = out_path[path_len - i - 1];
		out_path[path_len - i - 1] = tmp;
		i++;
	}
	return (path_len);
}

int	is_valid_neighbor(t_data *data, t_astar_data *astar, int nx, int ny)
{
	if (nx < 0 || nx >= astar->width || ny < 0 || ny >= astar->height)
		return (0);
	if (!is_valid_position(data, nx, ny))
		return (0);
	return (1);
}

void	add_neighbor(t_neighbor_context *ctx,
			t_astar_node *curr, int nx, int ny)
{
	t_astar_node	*next;

	next = &ctx->astar->nodes[ctx->astar->node_count++];
	next->pos.x = nx;
	next->pos.y = ny;
	next->g_cost = curr->g_cost + 1;
	next->h_cost = heuristic((t_pos){nx, ny}, ctx->goal);
	next->f_cost = next->g_cost + next->h_cost;
	next->parent = curr;
	next->open = 1;
	next->closed = 0;
}
