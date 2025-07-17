/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse_config_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:58:38 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/16 02:48:58 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int  parse_config_line(char *line, t_config *config);

int	parse_config_section(char **all_lines, t_config *config)
{
	int	i;
	
	i = 0;
	while (all_lines[i])
	{
		if (u_is_empty_line(all_lines[i]))
		{
			i++;
			continue;
		}
		if (u_is_config_line(all_lines[i]))
		{
			if (!parse_config_line(all_lines[i], config))
				return (0);
			config->config_lines++;
		}
		else
			break;
		i++;
	}
	return (1);
}

static int parse_config_line(char *line, t_config *config)
{
    char *trimmed;
    char **tokens;
    int result = 0;
    
    (void) config;
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
    // if (ft_strcmp(tokens[0], "NO") == 0 && tokens[1])
    //     result = set_texture(&config->path.north, tokens[1]);
    // else if (ft_strncmp(tokens[0], "SO", 2) == 0 && tokens[1])
    //     result = set_texture(&config->path.south, tokens[1]);
    // else if (ft_strncmp(tokens[0], "WE", 2) == 0 && tokens[1])
    //     result = set_texture(&config->path.west, tokens[1]);
    // else if (ft_strncmp(tokens[0], "EA", 2) == 0 && tokens[1])
    //     result = set_texture(&config->path.east, tokens[1]);
    // else if (ft_strncmp(tokens[0], "F", 2) == 0 && tokens[1])
    //     result = parse_color(tokens[1], &config->floor);
    // else if (ft_strncmp(tokens[0], "C", 2) == 0 && tokens[1])
    //     result = parse_color(tokens[1], &config->ceiling);
    free(trimmed);
    return (result);
}
