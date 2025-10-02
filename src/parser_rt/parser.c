/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:07:15 by natrodri          #+#    #+#             */
/*   Updated: 2025/10/02 13:19:06 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	verify_file(char *file)
{
	int	fd;
	int	i;
	int	cmp;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("deu ruim no fd paizao");
		exit(-1);
	}
	i = ft_strlen(file);
	i -= 3;
	cmp = ft_strncmp(&file[i], ".rt", 3);
	if (cmp != 0)
	{
		printf("o arquivo nao e .rt paizao");
		exit (-1);
	}
	return (fd);
}

void	set_prefix(char *str, t_scene *scene, int fd, int *i)
{
	if (str[*i] == 'A')
		creat_ambient(&str[*i], scene, str, fd);
	else if (str[*i] == 'C')
		parse_camera(&str[*i], scene, str, fd);
	else if (str[*i] == 'L')
		parse_light(&str[*i], scene, str, fd);
	else if (str[*i] == 's' && str[*i + 1] == 'p')
		parse_sphere(&str[*i], scene, str, fd);
	else if (str[*i] == 'p' && str[*i + 1] == 'l')
		parse_plane(&str[*i], scene, str, fd);
	else if (str[*i] == 'c' && str[*i + 1] == 'y')
		parse_cylinder(&str[*i], scene, str, fd);
	else
		bad(NULL, scene, str, fd);
}

void	read_file(int fd, t_scene *scene)
{
	int		i;
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		i = 0;
		while (str[i] == 32 || (str[i] > 6 && str[i] < 14))
			i++;
		if (str[i] == '\0')
		{
			free(str);
			str = get_next_line(fd);
			continue ;
		}
		if (str[i] >= 32 && str[i] <= 126)
			set_prefix(str, scene, fd, &i);
		free(str);
		str = get_next_line(fd);
	}
}

void	parser_rt(char *file, t_scene *scene)
{
	int	fd;

	fd = verify_file(file);
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	read_file(fd, scene);
	close(fd);
}
