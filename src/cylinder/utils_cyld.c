 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cyld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/25 12:04:11 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	update_hit(int i, double *closest_t, int *hit_found, t_intersections xs)
{
	*closest_t = xs.t[i];
	*hit_found = 1;
}

void	add_intersection(t_intersections *xs, double t)
{
	if (xs->count < 4)
	{
		xs->t[xs->count] = t;
		xs->count++;
	}
}

int	bhaskara(double *abc, double *t0, double *t1)
{
	double	discriminant;
	double	temp;

	discriminant = (abc[1] * abc[1]) - (4.0 * abc[0] * abc[2]);
	if (discriminant < 0)
		return (0);
	discriminant = sqrt(discriminant);
	*t0 = (-abc[1] - discriminant) / (2.0 * abc[0]);
	*t1 = (-abc[1] + discriminant) / (2.0 * abc[0]);
	if (*t0 > *t1)
	{
		temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return (1);
}

int	check_cap(t_cylinder *cyl, t_ray r, double t)
{
	t_vec3	p;
	t_vec3	oc;
	double	dist_sq;

	p = ray_at(r, t);
	oc = vec3_sub(p, cyl->center);
	dist_sq = vec3_length_squared(oc) - pow(vec3_dot(oc, cyl->axis), 2);
	return (dist_sq <= (cyl->radius * cyl->radius) + EPSILON);
}