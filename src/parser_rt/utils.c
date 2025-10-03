/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:07:15 by natrodri          #+#    #+#             */
/*   Updated: 2025/10/03 13:13:02 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	set_color(char **tok, int *color)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(tok[i], " \t\r\n");
		if (!trimmed || !vf_color(trimmed))
		{
			if (trimmed)
				free(trimmed);
			free_split(tok);
			return (0);
		}
		color[i] = ft_atoi(trimmed);
		free(trimmed);
		i++;
	}
	return (1);
}

int	check_commas(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (str[0] == ',' || str[ft_strlen(str) - 1] == ',')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (0);
		i++;
	}
	return (1);
}

int	convert_vec(char *str, double *vec)
{
	char	**tok;
	int		i;

	if (!check_commas(str))
		return (printf("vetor invalido paizao\n"), 0);
	tok = ft_split(str, ',');
	i = 0;
	while (tok[i])
		i++;
	if (i != 3)
	{
		free_split(tok);
		return (printf("vetor invalido paizao\n"), 0);
	}
	if (!vf_float(tok[0]) || !vf_float(tok[1]) || !vf_float(tok[2]))
		return (0);
	vec[0] = ft_atof(tok[0]);
	vec[1] = ft_atof(tok[1]);
	vec[2] = ft_atof(tok[2]);
	free_split(tok);
	return (1);
}

int	convert_color(char *str, int *color)
{
	char	**tok;
	int		i;

	if (!check_commas(str))
		return (printf("cor invalida paizao\n"), 0);
	tok = ft_split(str, ',');
	i = 0;
	while (tok[i])
		i++;
	if (i != 3)
	{
		free_split(tok);
		return (printf("cor invalida paizao\n"), 0);
	}
	set_color(tok, color);
	free_split(tok);
	return (1);
}

void	all_free(t_scene *scene)
{
	free_spheres(scene->spheres);
	free_planes(scene->planes);
	free_lights(scene->lights);
	free_cylinders(scene->cylinders);
}
