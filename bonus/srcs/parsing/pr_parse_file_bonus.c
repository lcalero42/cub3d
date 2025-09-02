/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_parse_file_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/02 17:23:34 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d_bonus.h"

static int	open_and_validate_file(char *filename);
static int	process_file_content(char *buf, t_data *data);
static char	*read_entire_file(int fd);

int	parse_file(char *filename, t_data *data)
{
	int		fd;
	char	*buf;

	fd = open_and_validate_file(filename);
	if (fd < 0)
		return (1);
	buf = read_entire_file(fd);
	close(fd);
	if (!buf)
		return (1);
	if (process_file_content(buf, data))
		return (1);
	free(buf);
	if (check_map(data))
		return (1);
	if (find_player_pos(data))
		return (1);
	return (0);
}

static int	open_and_validate_file(char *filename)
{
	int	fd;

	if (check_file_extension(filename))
	{
		u_print_error("File extension (.cub needed)");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		u_print_error("fd error");
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
	{
		free(buf);
		return (1);
	}
	return (0);
}
