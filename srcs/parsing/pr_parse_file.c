/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:32:10 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/18 02:18:38 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_file(char *filename, t_data *data)
{
	
	int		fd;
	char	*line;
	char	*buf;
	char	*tmp;
	char	**all_lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		printf("fd error\n");
	buf = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(buf, line);
		free(buf);
		free(line);
		if (!tmp)
			return (close(fd), 1);
		buf = tmp;
		line = get_next_line(fd);
	}
	close(fd);
	all_lines = ft_split(buf, '\n');
	parse_config_section(all_lines, data);
	parse_map(all_lines, data);
	free(buf);
	return (0);
}
