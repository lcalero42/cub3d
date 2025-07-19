/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_config_lines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:58:38 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/19 12:48:39 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_config_line(char *line, t_data *data);

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

	result = 0;
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	tokens = ft_split(trimmed, ' ');
	if (!tokens || !tokens[0])
	{
		free(trimmed);
		return (0);
	}
	if (ft_strncmp(tokens[0], "NO", 2) == 0 && tokens[1])
		result = parse_texture_path(&data->north_wall.info.addr, tokens[1]);
	else if (ft_strncmp(tokens[0], "SO", 2) == 0 && tokens[1])
		result = parse_texture_path(&data->south_wall.info.addr, tokens[1]);
	else if (ft_strncmp(tokens[0], "WE", 2) == 0 && tokens[1])
		result = parse_texture_path(&data->west_wall.info.addr, tokens[1]);
	else if (ft_strncmp(tokens[0], "EA", 2) == 0 && tokens[1])
		result = parse_texture_path(&data->east_wall.info.addr, tokens[1]);
	else if (ft_strncmp(tokens[0], "F", 2) == 0 && tokens[1])
		result = parse_color(tokens[1], &data->floor);
	else if (ft_strncmp(tokens[0], "C", 2) == 0 && tokens[1])
		result = parse_color(tokens[1], &data->ceiling);
	free(trimmed);
	u_ft_free(tokens);
	return (result);
}
