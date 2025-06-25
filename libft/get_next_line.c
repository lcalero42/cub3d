/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:20:00 by lcalero           #+#    #+#             */
/*   Updated: 2025/01/22 19:08:44 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/so_long.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	j;

	j = 0;
	len_s1 = ft_strlen(s1);
	while (s2[j] != '\n' && s2[j])
		j++;
	if (s2[j] == '\n')
		j++;
	res = malloc((len_s1 + j + 1) * sizeof(char));
	if (res == NULL)
		return (free(s1), NULL);
	ft_memcpy(res, s1, len_s1);
	ft_memcpy(res + len_s1, s2, j);
	res[len_s1 + j] = '\0';
	free(s1);
	return (res);
}

void	ft_update(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i])
		str[j++] = str[i++];
	str[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1] = {0};
	char			*line;
	int				index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	index = 1;
	line = ft_strdup(buffer);
	if (!line)
		return (NULL);
	while (index > 0 && !ft_strchr(line, '\n'))
	{
		index = read(fd, buffer, BUFFER_SIZE);
		if (index == -1)
			return (ft_bzero(buffer, BUFFER_SIZE), free(line), NULL);
		buffer[index] = '\0';
		line = ft_strjoin_free(line, buffer);
		if (!line)
			return (NULL);
	}
	if (index == 0 && !line[0])
		return (free(line), NULL);
	ft_update(buffer);
	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		//printf("%s", line);
		free(line);
	}
	return (0);
}*/