/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_enemy_find_path_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:37:20 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/24 18:55:31 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	process_neighbors_with_visited(t_neighbor_context *ctx,
				t_astar_node *curr);
static void	init_directions(int dirs[4][2]);

int	find_astar_path(t_data *data, t_pos start, t_pos goal, t_pos *out_path)
{
	t_astar_data		astar;
	t_neighbor_context	ctx;
	int					lowest;
	t_astar_node		*curr;
	int					visited[MAX_GRID_HEIGHT][MAX_GRID_WIDTH];

	ft_memset(astar.nodes, 0, sizeof(astar.nodes));
	ft_memset(visited, 0, sizeof(visited));
	init_astar_data(data, &astar, start, goal);
	ctx = (t_neighbor_context){data, &astar, goal, visited};
	while (1)
	{
		lowest = find_lowest_f_cost(&astar);
		if (lowest == -1)
			break ;
		curr = &astar.nodes[lowest];
		curr->open = 0;
		curr->closed = 1;
		if (curr->pos.x == goal.x && curr->pos.y == goal.y)
			return (reconstruct_path(curr, out_path, MAX_NODES));
		process_neighbors_with_visited(&ctx, curr);
	}
	return (0);
}

static void	process_neighbors_with_visited(t_neighbor_context *ctx,
	t_astar_node *curr)
{
	int	dirs[4][2];
	int	d;
	int	nx;
	int	ny;

	init_directions(dirs);
	d = 0;
	while (d < 4)
	{
		nx = curr->pos.x + dirs[d][0];
		ny = curr->pos.y + dirs[d][1];
		if (is_valid_neighbor(ctx->data, ctx->astar, nx, ny)
			&& !ctx->visited[ny][nx])
		{
			add_neighbor(ctx, curr, nx, ny);
			ctx->visited[ny][nx] = 1;
			if (ctx->astar->node_count >= MAX_NODES)
				break ;
		}
		d++;
	}
}

static void	init_directions(int dirs[4][2])
{
	dirs[0][0] = 0;
	dirs[0][1] = 1;
	dirs[1][0] = 1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = -1;
	dirs[3][0] = -1;
	dirs[3][1] = 0;
}

int	is_valid_position(t_data *data, double x, double y)
{
	int		map_x;
	int		map_y;
	t_door	*door;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= data->grid.width
		|| map_y < 0 || map_y >= data->grid.height)
		return (0);
	if (data->grid.grid[map_y][map_x] == '2')
	{
		door = find_door_at(data, map_x, map_y);
		if (door)
		{
			if (door->state == DOOR_CLOSED)
				return (0);
		}
	}
	return (data->grid.grid[map_y][map_x] != '1');
}

int	heuristic(t_pos a, t_pos b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
}
