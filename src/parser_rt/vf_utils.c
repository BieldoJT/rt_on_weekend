/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:12:36 by natrodri          #+#    #+#             */
/*   Updated: 2025/10/03 14:41:42 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	vf_float(const char *str)
{
	int	i;
	int	has_dot;
	int	has_digit;

	i = 0;
	has_digit = 0;
	has_dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digit = 1;
		else if (str[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else
			return (0);
		i++;
	}
	return (has_digit);
}

int	vf_color(char *str)
{
	int		i;
	int		value;

	i = 0;
	if (!str || !*str)
		return (0);
	if (!vf_float(str))
		return (0);
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		return (0);
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		i++;
		while (str[i])
		{
			if (str[i] != '0')
				return (0);
			i++;
		}
	}
	return (1);
}

void	bad(char **tok, t_scene *scene, char *line, int fd)
{
	free_split(tok);
	all_free(scene);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	printf("Error\n");
	exit(1);
}
