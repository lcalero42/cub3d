/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_map_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:48:20 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/18 18:51:02 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_double_newline(char *all_lines, int j,
		int i, int last_newline)
{
	int	only_whitespace;
	int	temp;

	if (last_newline == -1 || all_lines[j] != '\n')
		return (-1);
	only_whitespace = 1;
	while (i < j)
	{
		if (!(((all_lines[i] >= 7 && all_lines[i] <= 13)
					&& all_lines[i] != '\n') || all_lines[i] == ' '))
		{
			only_whitespace = 0;
			break ;
		}
		i++;
	}
	if (only_whitespace)
	{
		temp = j;
		while (all_lines[temp] && !ft_isalnum(all_lines[temp]))
			temp++;
		if (ft_isalnum(all_lines[temp]))
			return (0);
	}
	return (-1);
}

int	check_map_content(char *all_lines)
{
	int	j;
	int	last_newline;
	int	result;

	last_newline = -1;
	j = map_start_buff(all_lines);
	while (all_lines[j])
	{
		if (((all_lines[j] >= 7 && all_lines[j] <= 13)
				&& all_lines[j] != '\n') || all_lines[j] == ' ')
		{
			j++;
			continue ;
		}
		result = check_double_newline(all_lines, j,
				last_newline + 1, last_newline);
		if (result == 0)
			return (0);
		if (all_lines[j] == '\n')
			last_newline = j;
		j++;
	}
	return (1);
}

static int	find_line_end(char *s, int start)
{
	int	end;

	end = start;
	while (s[end] && s[end] != '\n')
		end++;
	return (end);
}

static int	process_config_line(char *all_lines, int *i, int *line_start)
{
	int		line_end;
	char	*line;
	int		is_config;

	line_end = find_line_end(all_lines, *i);
	line = ft_substr(all_lines, *line_start, line_end - *line_start);
	if (!line)
		return (-1);
	is_config = u_is_config_line(line);
	free(line);
	if (all_lines[line_end] == '\n')
		*i = line_end + 1;
	else
		*i = line_end;
	*line_start = *i;
	return (is_config);
}

int	map_start_buff(char *all_lines)
{
	int		i;
	int		conf_element;
	int		line_start;
	int		result;
	char	*all_lines_cpy;

	i = 0;
	conf_element = 0;
	line_start = 0;
	all_lines_cpy = ft_strtrim(all_lines, " \n");
	while (conf_element < 6 && all_lines_cpy[i])
	{
		result = process_config_line(all_lines_cpy, &i, &line_start);
		if (result == -1)
			return (-1);
		if (result == 1)
			conf_element++;
	}
	free(all_lines_cpy);
	return (skip_whitespace(all_lines, i));
}
