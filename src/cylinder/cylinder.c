/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/09/26 16:37:59 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void	intersect_caps(t_cylinder *cyl, t_ray r, t_intersections *xs)
{
	double	denom;
	double	t;
	t_vec3	cap_p;

	denom = vec3_dot(r.dir, cyl->axis);
	if (fabs(denom) < EPSILON)
		return ;
	cap_p = vec3_add(cyl->center, vec3_mul(cyl->axis, -cyl->height / 2.0));
	t = vec3_dot(vec3_sub(cap_p, r.orig), cyl->axis) / denom;
	if (check_cap(cyl, r, t))
		add_intersection(xs, t);
	cap_p = vec3_add(cyl->center, vec3_mul(cyl->axis, cyl->height / 2.0));
	t = vec3_dot(vec3_sub(cap_p, r.orig), cyl->axis) / denom;
	if (check_cap(cyl, r, t))
		add_intersection(xs, t);
}

static void	intersect_walls(t_cylinder *cyl, t_ray r, t_intersections *xs)
{
	t_vec3	oc;
	double	abc[3];
	double	t[2];
	double	y;

	oc = vec3_sub(r.orig, cyl->center);
	abc[0] = vec3_length_squared(r.dir) - pow(vec3_dot(r.dir, cyl->axis), 2);
	abc[1] = 2 * (vec3_dot(r.dir, oc) - (vec3_dot(r.dir, cyl->axis)
				* vec3_dot(oc, cyl->axis)));
	abc[2] = vec3_length_squared(oc) - pow(vec3_dot(oc, cyl->axis), 2)
		- (cyl->radius * cyl->radius);
	if (fabs(abc[0]) < EPSILON)
		return ;
	if (!bhaskara(abc, &t[0], &t[1]))
		return ;
	y = vec3_dot(vec3_sub(ray_at(r, t[0]), cyl->center), cyl->axis);
	if (y > -cyl->height / 2.0 && y < cyl->height / 2.0)
		add_intersection(xs, t[0]);
	y = vec3_dot(vec3_sub(ray_at(r, t[1]), cyl->center), cyl->axis);
	if (y > -cyl->height / 2.0 && y < cyl->height / 2.0)
		add_intersection(xs, t[1]);
}

static t_vec3	get_cylinder_normal_at(t_cylinder *cyl, t_vec3 p)
{
	t_vec3	oc;
	t_vec3	projected;
	double	dist;
	double	half_height;

	oc = vec3_sub(p, cyl->center);
	dist = vec3_dot(oc, cyl->axis);
	half_height = cyl->height / 2.0;
	if (dist >= half_height - EPSILON)
		return (cyl->axis);
	if (dist <= -half_height + EPSILON)
		return (vec3_mul(cyl->axis, -1.0));
	else
	{
		projected = vec3_mul(cyl->axis, dist);
		return (vec3_unit_vector(vec3_sub(oc, projected)));
	}
}

int	hit_cylinder(t_cylinder *cld, t_ray r, t_interval tr, t_hit_record *rec)
{
	t_intersections	xs;
	int				i;
	int				hit_found;
	double			closest_t;

	xs.count = 0;
	intersect_walls(cld, r, &xs);
	intersect_caps(cld, r, &xs);
	if (xs.count == 0)
		return (0);
	hit_found = 0;
	closest_t = tr.max;
	i = -1;
	while (++i < xs.count)
		if (xs.t[i] > tr.min && xs.t[i] < closest_t)
			update_hit(i, &closest_t, &hit_found, xs);
	if (!hit_found)
		return (0);
	rec->t = closest_t;
	rec->p = ray_at(r, rec->t);
	rec->normal = get_cylinder_normal_at(cld, rec->p);
	rec->material = cld->material;
	return (1);
}

t_hittable	*cylinder_create(t_vec3 center, t_vec3 axis,
	double *ra_and_he, t_material *mat)
{
	t_hittable	*hittable_obj;
	t_cylinder	*cylinder_data;

	if (ra_and_he[0] <= 0.0 || ra_and_he[1] <= 0.0)
		return (NULL);
	hittable_obj = malloc(sizeof(t_hittable));
	cylinder_data = malloc(sizeof(t_cylinder));
	if (!hittable_obj || !cylinder_data)
		return (NULL);
	cylinder_data->center = center;
	cylinder_data->axis = vec3_unit_vector(axis);
	cylinder_data->radius = ra_and_he[0];
	cylinder_data->height = ra_and_he[1];
	cylinder_data->material = mat;
	hittable_obj->obj = cylinder_data;
	hittable_obj->hit = (int (*)(void *, t_ray, t_interval,
				t_hit_record *))hit_cylinder;
	return (hittable_obj);
}