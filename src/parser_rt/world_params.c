/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:07:15 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 18:10:51 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	creat_ambient(char *str, t_scene *scene, char *line, int fd)
{
	char	**tok;
	int		i;

	tok = ft_split(str, ' ');
	i = 0;
	while (tok[i])
		i++;
	if (i != 3)
		bad(tok, scene, line, fd);
	scene->ambient.intensity = ft_atof(tok[1]);
	if (!convert_color(tok[2], scene->ambient.color))
		bad(tok, scene, line, fd);
	free_split(tok);
}

void	parse_camera(char *str, t_scene *scene, char *line, int fd)
{
	char	**tok;
	int		i;

	tok = ft_split(str, ' ');
	i = 0;
	while (tok[i])
		i++;
	if (i != 4)
		bad(tok, scene, line, fd);
	if (!convert_vec(tok[1], scene->camera.pos) || !convert_vec(tok[2],
			scene->camera.orientation))
		bad(tok, scene, line, fd);
	scene->camera.fov = ft_atof(tok[3]);
	free_split(tok);
}

void	parse_light(char *str, t_scene *scene, char *line, int fd)
{
	char		**tok;
	t_prs_light	*light;
	int			i;

	tok = ft_split(str, ' ');
	i = 0;
	while (tok[i])
		i++;
	if (i != 4)
		bad(tok, scene, line, fd);
	light = malloc(sizeof(t_prs_light));
	if (!light)
		bad(tok, scene, line, fd);
	if (!convert_vec(tok[1], light->pos) || !convert_color(tok[3],
			light->color))
	{
		free(light);
		bad(tok, scene, line, fd);
	}
	light->intensity = ft_atof(tok[2]);
	light->next = scene->lights;
	scene->lights = light;
	free_split(tok);
}
