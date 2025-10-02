/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:07:15 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 18:10:51 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_lights(t_prs_light *light)
{
	t_prs_light	*tmp;

	while (light)
	{
		tmp = light->next;
		free(light);
		light = tmp;
	}
}

void	free_spheres(t_prs_sphere *s)
{
	t_prs_sphere	*tmp;

	while (s)
	{
		tmp = s->next;
		free(s);
		s = tmp;
	}
}

void	free_planes(t_prs_plane *p)
{
	t_prs_plane	*tmp;

	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

void	free_cylinders(t_prs_cylinder *cy)
{
	t_prs_cylinder	*tmp;

	while (cy)
	{
		tmp = cy->next;
		free(cy);
		cy = tmp;
	}
}

void	free_split(char **tok)
{
	int	i;

	if (!tok)
		return ;
	i = 0;
	while (tok[i])
		free(tok[i++]);
	free(tok);
}
