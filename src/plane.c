/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/25 12:04:11 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	plane_hit(void *obj, t_ray r, t_interval t_range, t_hit_record *rec)
{
	t_plane	*pl;
	double	denomi;
	double	num;
	double	t;

	pl = (t_plane *)obj;
	denomi = vec3_dot(r.dir, pl->norma);
	if (fabs(denomi) < 1e-6)
		return (0);
	num = vec3_dot(vec3_sub(pl->point, r.orig), pl->norma);
	t = num / denomi;
	if (!interval_contains(&t_range, t))
		return (0);
	rec->t = t;
	rec->p = ray_at(r, t);
	rec->material = pl->material;
	set_face_normal(rec, r, pl->norma);
	return (1);
}

t_hittable	*plane_creat(t_vec3 point, t_vec3 norma, t_material *material)
{
	t_hittable	*ht;
	t_plane		*pl;

	ht = malloc(sizeof(*ht) + sizeof(*pl));
	if (!ht)
		return (NULL);
	pl = (t_plane *)(ht + 1);
	ht->obj = pl;
	pl->point = point;
	pl->norma = vec3_unit_vector(norma);
	pl->material = material;
	ht->hit = plane_hit;
	return (ht);
}