/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_config_lines_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/02 17:23:22 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

static int	parse_config_line(char *line, t_data *data);
static int	process_config_tokens(char **tokens, char *full_line, t_data *data);
static int	parse_wall_texture(char *key, char *value, t_data *data);
static int	parse_color_config(char *key, char *full_line, t_data *data);

int	parse_config_section(char **all_lines, t_data *data)
{
	int	i;

	i = 0;
	while (all_lines[i])
	{
		if (u_is_empty_line(all_lines[i]))
		{
			i++;
			continue ;
		}
		if (u_is_config_line(all_lines[i]))
		{
			if (!parse_config_line(all_lines[i], data))
				return (0);
			data->config_lines++;
		}
		else
			break ;
		i++;
	}
	return (1);
}

static int	parse_config_line(char *line, t_data *data)
{
	char	*trimmed;
	char	**tokens;
	int		result;

	trimmed = ft_strtrim(line, " \t\n ");
	if (!trimmed)
		return (0);
	tokens = ft_split(trimmed, ' ');
	if (!tokens || !tokens[0])
	{
		free(trimmed);
		return (0);
	}
	result = process_config_tokens(tokens, trimmed, data);
	free(trimmed);
	u_ft_free(tokens);
	return (result);
}

static int	process_config_tokens(char **tokens, char *full_line, t_data *data)
{
	int		result;

	result = 0;
	if (!tokens[1])
		return (0);
	result = parse_wall_texture(tokens[0], tokens[1], data);
	if (result == 0)
		result = parse_color_config(tokens[0], full_line, data);
	return (result);
}

static int	parse_wall_texture(char *key, char *value, t_data *data)
{
	if (ft_strncmp(key, "NO", 2) == 0)
		return (parse_texture_path(&data->north_wall.texture_path, value));
	else if (ft_strncmp(key, "SO", 2) == 0)
		return (parse_texture_path(&data->south_wall.texture_path, value));
	else if (ft_strncmp(key, "WE", 2) == 0)
		return (parse_texture_path(&data->west_wall.texture_path, value));
	else if (ft_strncmp(key, "EA", 2) == 0)
		return (parse_texture_path(&data->east_wall.texture_path, value));
	return (0);
}

static int	parse_color_config(char *key, char *full_line, t_data *data)
{
	if (ft_strncmp(key, "F", 1) == 0)
		return (parse_color(full_line, &data->floor));
	else if (ft_strncmp(key, "C", 1) == 0)
		return (parse_color(full_line, &data->ceiling));
	return (0);
}
