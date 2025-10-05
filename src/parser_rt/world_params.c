/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:07:15 by natrodri          #+#    #+#             */
/*   Updated: 2025/10/04 13:35:27 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	creat_ambient(char *str, t_scene *scene, char *line, int fd)
{
	char			**tok;
	double			intens;
	t_prs_ambient	*ambient;
	int				i;

	tok = ft_split2(str, "\t ");
	i = 0;
	while (tok[i])
		i++;
	if (i != 3)
		bad(tok, scene, line, fd);
	ambient = malloc(sizeof(t_prs_ambient));
	if (!ambient)
		bad(tok, scene, line, fd);
	intens = ft_atof(tok[1]);
	ambient->intensity = intens;
	if (intens < 0.0 || intens > 1.0
		|| !convert_color(tok[2], ambient->color))
	{
		free(ambient);
		bad(tok, scene, line, fd);
	}
	scene->ambient = ambient;
	free_split(tok);
}

int	verify_normalize(char *str)
{
	char	**tok;
	double	val;
	int		i;

	if (!check_commas(str))
		return (0);
	tok = ft_split(str, ',');
	if (!tok)
		return (0);
	i = 0;
	while (tok[i])
		i++;
	if (i != 3)
		return (free_split(tok), 0);
	i = 0;
	while (i < 3)
	{
		if (!vf_float(tok[i]))
			return (free_split(tok), 0);
		val = ft_atof(tok[i]);
		if (val < -1.0 || val > 1.0)
			return (free_split(tok), 0);
		i++;
	}
	return (free_split(tok), 1);
}

void	parse_camera(char *str, t_scene *scene, char *line, int fd)
{
	char	**tok;
	double	fov;
	int		i;

	tok = ft_split2(str, "\t ");
	i = 0;
	while (tok[i])
		i++;
	if (i != 4)
		bad(tok, scene, line, fd);
	if (!verify_normalize(tok[2]))
		bad(tok, scene, line, fd);
	if (!convert_vec(tok[1], scene->camera.pos) || !convert_vec(tok[2],
			scene->camera.orientation))
		bad(tok, scene, line, fd);
	fov = ft_atof(tok[3]);
	if (!(fov >= 0.0 && fov <= 180.0))
		bad(tok, scene, line, fd);
	scene->camera.fov = fov;
	free_split(tok);
}

void	parse_light(char *str, t_scene *scene, char *line, int fd)
{
	char		**tok;
	t_prs_light	*light;
	int			i;

	tok = ft_split2(str, "\t ");
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
	if (ft_atof(tok[2]) < 0.0 || ft_atof(tok[2]) > 1.0)
		bad(tok, scene, line, fd);
	light->intensity = ft_atof(tok[2]);
	light->next = scene->lights;
	scene->lights = light;
	free_split(tok);
}
