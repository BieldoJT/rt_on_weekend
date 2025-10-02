/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:13:40 by gda-conc          #+#    #+#             */
/*   Updated: 2025/09/24 04:36:31 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int	hit_anything(t_rt *rt, t_ray r, double tmax)
{
	t_hit_record	rec;
	t_interval		shadow_rng;

	interval_init(&shadow_rng, 0.001, tmax);
	return (hit_world(r, &rec, rt) != 0);
}

int	shadow_blocked(t_rt *rt, t_vec3 p, t_vec3 to_l, double dist_l)
{
	t_ray	r;

	r = ray(p, to_l);
	return (hit_anything(rt, r, dist_l - 1e-4));
}

t_vec3	point_light_diffuse(t_rt *rt, const t_hit_record *rec, int i)
{
	t_vec3	lo;
	t_vec3	nl;
	double	dist;
	double	n_dot_l;
	t_vec3	c;

	lo = vec3_sub(rt->lights[i]->position, rec->p);
	dist = vec3_length(lo);
	if (dist <= 0.0)
		return (vec3(0, 0, 0));
	nl = vec3_unit_vector(lo);
	if (shadow_blocked(rt, rec->p, nl, dist))
		return (vec3(0, 0, 0));
	n_dot_l = vec3_dot(rec->normal, nl);
	if (n_dot_l <= 0.0)
		return (vec3(0, 0, 0));
	c = vec3_div(rt->lights[i]->intensity, (dist * dist));
	return (vec3_mul(vec3_mult_vecs(rec->material->albedo, c), n_dot_l));
}

int	rr_terminate(t_vec3 *atten)
{
	double	probability;

	probability = atten->x;
	if (atten->y > probability)
		probability = atten->y;
	if (atten->z > probability)
		probability = atten->z;
	if (probability < 0.1)
		probability = 0.1;
	if (random_double() > probability)
		return (1);
	*atten = vec3_div(*atten, probability);
	return (0);
}

t_vec3	ambient_term(t_rt *rt, const t_hit_record *rec)
{
	t_vec3	ia;
	t_vec3	out;

	ia = vec3_mul(rt->ambient.color, rt->ambient.ratio);
	out = vec3_mult_vecs(ia, rec->material->albedo);
	return (out);
}
