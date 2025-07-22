/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:32:10 by ekeisler          #+#    #+#             */
/*   Updated: 2025/07/22 12:13:52 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_and_validate_file(char *filename);
static int	process_file_content(char *buf, t_data *data);
static char	*read_entire_file(int fd);

int	parse_file(char *filename, t_data *data)
{
	int		fd;
	char	*buf;
	int		result;

	fd = open_and_validate_file(filename);
	if (fd < 0)
		return (1);
	buf = read_entire_file(fd);
	close(fd);
	if (!buf)
		return (1);
	result = process_file_content(buf, data);
	free(buf);
	return (result);
}

static int	open_and_validate_file(char *filename)
{
	int	fd;

	if (check_file_extension(filename))
	{
		printf("error: file extension\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("fd error\n");
		return (-1);
	}
	return (fd);
}

static char	*read_entire_file(int fd)
{
	char	*line;
	char	*buf;
	char	*tmp;

	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(buf, line);
		free(buf);
		free(line);
		if (!tmp)
			return (NULL);
		buf = tmp;
		line = get_next_line(fd);
	}
	return (buf);
}

static int	process_file_content(char *buf, t_data *data)
{
	char	**all_lines;

	all_lines = ft_split(buf, '\n');
	if (!all_lines)
		return (1);
	parse_config_section(all_lines, data);
	parse_map(all_lines, data);
	u_ft_free(all_lines);
	if (0 == validate_config(data))
		return (1);
	return (0);
}
