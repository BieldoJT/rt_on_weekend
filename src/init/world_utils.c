/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:43:32 by natrodri          #+#    #+#             */
/*   Updated: 2025/10/04 13:56:26 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int	count_obj(t_scene *scene)
{
	int				i;
	t_prs_cylinder	*cyl;
	t_prs_plane		*pl;
	t_prs_sphere	*sp;

	i = 0;
	cyl = scene->cylinders;
	pl = scene->planes;
	sp = scene->spheres;
	while (cyl)
	{
		i++;
		cyl = cyl->next;
	}
	while (pl)
	{
		i++;
		pl = pl->next;
	}
	while (sp)
	{
		i++;
		sp = sp->next;
	}
	return (i);
}

int	count_lights(t_prs_light *light)
{
	int			i;
	t_prs_light	*tmp;

	i = 0;
	tmp = light;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
