/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:16:33 by natrodri          #+#    #+#             */
/*   Updated: 2024/10/25 08:06:47 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*save;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = remove_line(save);
	return (line);
}

/*int main()
{
    char    *retorno;
    int fd = open("file.txt", O_RDONLY);
    retorno = get_next_line(fd);
    printf("%s", retorno);
}*/
