/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:16:33 by natrodri          #+#    #+#             */
/*   Updated: 2024/10/25 09:13:26 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_file(int fd, char *backup)
{
	char	*buffer;
	int		count;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	count = 1;
	while (count > 0 && !ft_strchr2(backup, '\n'))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[count] = '\0';
		backup = ft_strjoin2(backup, buffer);
	}
	free(buffer);
	return (backup);
}

static char	*get_line(char	*save)
{
	char	*line;
	int		i;

	i = 0;
	if (!*save)
		return (NULL);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy2(line, save, i + 1);
	if (line[i] == '\n')
		i++;
	line[i] = '\0';
	return (line);
}

static char	*remove_line(char *save)
{
	int		l;
	int		i;
	char	*backup;

	i = 0;
	l = ft_strlen2(save);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free (save);
		return (NULL);
	}
	backup = malloc((l - i + 1) * sizeof(char));
	if (!backup)
		return (NULL);
	i++;
	l = 0;
	while (save[i])
		backup[l++] = save[i++];
	backup[l] = '\0';
	free(save);
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[MAX_FD];

	if (fd < 0 || BUFFER_SIZE < 1 || fd > MAX_FD)
		return (NULL);
	save[fd] = read_file(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = get_line(save[fd]);
	save[fd] = remove_line(save[fd]);
	return (line);
}
