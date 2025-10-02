/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:07:15 by natrodri          #+#    #+#             */
/*   Updated: 2025/10/02 17:36:44 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	add_mat(char *mat_tok, t_obj_param *object)
{
	if (!mat_tok)
		return ;
	if (mat_tok[0] == 'm' || mat_tok[0] == 'd')
	{
		object->material = mat_tok[0];
		object->param = ft_atof(mat_tok + 1);
	}
	else
	{
		object->material = 'l';
		object->param = 0.0;
	}
}

void	parse_sphere(char *str, t_scene *scene, char *line, int fd)
{
	char			**tok;
	t_prs_sphere	*sp;
	double			diameter;
	int				i;

	tok = ft_split(str, ' ');
	i = 0;
	while (tok[i])
		i++;
	if (i != 4 && i != 5)
		bad(tok, scene, line, fd);
	sp = malloc(sizeof(t_prs_sphere));
	if (!sp)
		bad(tok, scene, line, fd);
	if (!convert_vec(tok[1], sp->pos) || !convert_color(tok[3], sp->color))
	{
		free(sp);
		bad(tok, scene, line, fd);
	}
	add_mat(tok[i - 1], &sp->mat);
	diameter = ft_atof(tok[2]);
	if (diameter < 0.0)
		bad(tok, scene, line, fd);
	sp->radius = diameter / 2.0;
	sp->next = scene->spheres;
	scene->spheres = sp;
	free_split(tok);
}

void	parse_plane(char *str, t_scene *scene, char *line, int fd)
{
	char		**tok;
	t_prs_plane	*pl;
	int			i;

	tok = ft_split(str, ' ');
	i = 0;
	while (tok[i])
		i++;
	if (i != 4 && i != 5)
		bad(tok, scene, line, fd);
	pl = malloc(sizeof(t_prs_plane));
	if (!pl)
		bad(tok, scene, line, fd);
	if (!verify_normalize(tok[2]))
		bad(tok, scene, line, fd);
	if (!convert_vec(tok[1], pl->pos) || !convert_vec(tok[2],
			pl->orientation) || !convert_color(tok[3], pl->color))
	{
		free(pl);
		bad(tok, scene, line, fd);
	}
	pl->mat.material = 0;
	add_mat(tok[i], &pl->mat);
	pl->next = scene->planes;
	scene->planes = pl;
	free_split(tok);
}

void	parse_cylinder(char *str, t_scene *scene, char *line, int fd)
{
	char			**tok;
	t_prs_cylinder	*cy;
	int				i;

	tok = ft_split(str, ' ');
	i = 0;
	while (tok[i])
		i++;
	if (i != 6 && i != 7)
		bad(tok, scene, line, fd);
	cy = malloc(sizeof(t_prs_cylinder));
	if (!cy)
		bad(tok, scene, line, fd);
	if (!convert_vec(tok[1], cy->pos) || !convert_vec(tok[2],
			cy->orientation) || !convert_color(tok[5], cy->color))
	{
		free(cy);
		bad(tok, scene, line, fd);
	}
	add_mat(tok[i], &cy->mat);
	if (ft_atof(tok[3]) < 0.0 || ft_atof(tok[4]) < 0.0)
		bad(tok, scene, line, fd);
	cy->radius = ft_atof(tok[3]) / 2.0;
	cy->height = ft_atof(tok[4]);
	cy->next = scene->cylinders;
	scene->cylinders = cy;
	free_split(tok);
}
