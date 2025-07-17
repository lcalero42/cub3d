/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:53:44 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/16 02:54:46 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->window);
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	return (0);
}

int	render_loop(t_data *data)
{
	trace_ray(data, 0);
	return (1);
}

void	print_config_info_simple(t_config *config)
{
	printf("\n========== CONFIG PARSING INFO ==========\n");
	
	printf("Config lines parsed: %d\n", config->config_lines);
	printf("Map dimensions: %dx%d\n", config->map.width, config->map.height);
	printf("\nTextures:\n");
	printf("  NO: %s\n", config->path.north ? config->path.north : "NOT SET");
	printf("  SO: %s\n", config->path.south ? config->path.south : "NOT SET");
	printf("  WE: %s\n", config->path.west ? config->path.west : "NOT SET");
	printf("  EA: %s\n", config->path.east ? config->path.east : "NOT SET");
	
	printf("\nColors:\n");
	if (config->floor.r != -1)
		printf("  Floor: RGB(%d, %d, %d)\n", 
			   config->floor.r, config->floor.g, config->floor.b);
	else
		printf("  Floor: NOT SET\n");
	
	if (config->ceiling.r != -1)
		printf("  Ceiling: RGB(%d, %d, %d)\n", 
			   config->ceiling.r, config->ceiling.g, config->ceiling.b);
	else
		printf("  Ceiling: NOT SET\n");
	
	printf("\nMap:\n");
	if (config->map.grid)
	{
		for (int i = 0; i < config->map.height; i++)
			printf("  [%2d] %s\n", i, config->map.grid[i]);
	}
	else
	{
		printf("  NO MAP LOADED\n");
	}
	printf("==========================================\n\n");
}

int	main(void)
{
	t_config	config;
	
	init_config(&config);
	parse_file("map/test_parsing.cub", &config);
	// print_config_info_simple(&config);
	return (0);
}