/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:17:55 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/18 18:23:28 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

void	get_sphere_uv(t_vec3 *p, double *u, double *v)
{
	double	phi;
	double	theta;

	phi = atan2(p->z, p->x) + PI;
	theta = asin(p->y);
	*u = phi / (2.0 * PI);
	*v = theta / PI;
}

static void	fill_hit(t_hit_record *rec, t_sphere *sp, t_ray r)
{
	t_vec3	outward_normal;

	rec->p = ray_at(r, rec->t);
	outward_normal = vec3_div(vec3_sub(rec->p, sp->center),
			sp->radius);
	get_sphere_uv(&outward_normal, &rec->u, &rec->v);
	set_face_normal(rec, r, outward_normal);
	rec->material = sp->material;
}

int	sphere_hit(void *obj, t_ray r, t_interval t, t_hit_record *rec)
{
	t_equation	eq;
	t_sphere	*sp;
	double		sqrtd;
	double		root;

	sp = obj;
	eq.oc = vec3_sub(r.orig, sp->center);
	eq.a = vec3_length_squared(r.dir);
	eq.half_b = vec3_dot(r.dir, eq.oc);
	eq.c = vec3_length_squared(eq.oc) - sp->radius * sp->radius;
	eq.disc = eq.half_b * eq.half_b - eq.a * eq.c;
	if (eq.disc < 0.0)
		return (0);
	sqrtd = sqrt(eq.disc);
	root = (-eq.half_b - sqrtd) / eq.a;
	if (root < t.min || root > t.max)
	{
		root = (-eq.half_b + sqrtd) / eq.a;
		if (root < t.min || root > t.max)
			return (0);
	}
	rec->t = root;
	fill_hit(rec, sp, r);
	return (1);
}

/*
** Cria o t_sphere e o envelopa num t_hittable
*/
t_hittable	*sphere_create(t_vec3 center, double radius, t_material *material)
{
	t_hittable	*ht;

	ht = malloc(sizeof(*ht) + sizeof(t_sphere));
	if (!ht)
		return (NULL);
	ht->obj = (void *)(ht + 1);
	((t_sphere *)ht->obj)->center = center;
	((t_sphere *)ht->obj)->radius = radius;
	((t_sphere *)ht->obj)->material = material;
	ht->hit = sphere_hit;
	return (ht);
}
