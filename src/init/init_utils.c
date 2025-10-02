/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/09/26 17:16:33 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_material	*choose_material(t_obj_param *mat, int *color)
{
	t_vec3		col;
	t_material	*mat_ptr;

	col = vec3(color[0] / 255.0, color[1] / 255.0, color[2] / 255.0);
	mat_ptr = NULL;
	if (mat->material == 'm')
		mat_ptr = metal_create(col, mat->param);
	else if (mat->material == 'd')
		mat_ptr = dielectric_create(mat->param);
	else
		mat_ptr = lambertian_create(col);
	return (mat_ptr);
}

void	add_sphere(t_prs_sphere *sph, t_rt *rt)
{
	while (sph)
	{
		rt->world[rt->world_size++] = sphere_create(
				vec3(sph->pos[0], sph->pos[1], sph->pos[2]),
				sph->radius, choose_material(&sph->mat, sph->color));
		sph = sph->next;
	}
}

void	add_plane(t_prs_plane *pl, t_rt *rt)
{
	while (pl)
	{
		rt->world[rt->world_size++] = plane_creat(
				vec3(pl->pos[0], pl->pos[1], pl->pos[2]),
				vec3(pl->orientation[0], pl->orientation[1],
					pl->orientation[2]), choose_material(&pl->mat, pl->color)
				);
		pl = pl->next;
	}
}

void	add_cylinder(t_prs_cylinder *cyl, t_rt *rt)
{
	double	ra_and_he[2];

	while (cyl)
	{
		ra_and_he[0] = cyl->radius;
		ra_and_he[1] = cyl->height;
		rt->world[rt->world_size++] = cylinder_create(
				vec3(cyl->pos[0], cyl->pos[1], cyl->pos[2]),
				vec3(cyl->orientation[0], cyl->orientation[1],
					cyl->orientation[2]),
				ra_and_he, choose_material(&cyl->mat, cyl->color)
				);
		cyl = cyl->next;
	}
}

void	add_lights(t_prs_light *lt, t_rt *rt)
{
	int			count;
	int			i;
	t_prs_light	*tmp;

	tmp = lt;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	rt->n_lights = count;
	rt->lights = malloc(sizeof(t_point_light *) * count);
	i = 0;
	while (lt)
	{
		rt->lights[i++] = point_light_create(
				vec3(lt->pos[0], lt->pos[1], lt->pos[2]),
				vec3(lt->color[0], lt->color[1], lt->color[2])
				);
		lt = lt->next;
	}
}
