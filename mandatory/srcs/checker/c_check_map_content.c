/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_check_map_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:39:36 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/12 18:46:56 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int map_start_buff(char *all_lines);

int	check_map_content(char *all_lines)
{
	int	j;
	int	found_endl;

	found_endl = -1;
	j = map_start_buff(all_lines);
	while (all_lines[j])
	{
		if (((all_lines[j] >= 7 && all_lines[j] <= 13) && all_lines[j] != '\n') || all_lines[j] == ' ')
		{
			j++;
			continue ;
		}
		if (j != 0)
			if (all_lines[j] == '\n' && all_lines[j - 1] && found_endl == j - 1)
				return (0);
		if (all_lines[j] == '\n')
			found_endl = j;
		j++;
	}
	return (1);
}

static int	map_start_buff(char *all_lines)
{
	int	i;
	int	conf_element;
	int	line_start;

	i = 0;
	conf_element = 0;
	line_start = 0;
	while (conf_element < 6 && all_lines[i])
	{
		int line_end = i;
		while (all_lines[line_end] && all_lines[line_end] != '\n')
			line_end++;
		char *line = ft_substr(all_lines, line_start, line_end - line_start);
		if (!line)
			return (-1);
		if (u_is_config_line(line))
			conf_element++;
		free(line);
		i = (all_lines[line_end] == '\n') ? line_end + 1 : line_end;
		line_start = i;
	}
	while (all_lines[i] && (all_lines[i] == ' ' || (all_lines[i] >= 7 && all_lines[i] <= 13)))
		i++;
	return (i);
}

