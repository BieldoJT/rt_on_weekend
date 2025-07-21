/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:35:39 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/18 17:54:23 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	hit_world(t_ray r, t_hit_record *rec, t_rt *rt)
{
	t_hit_record	tmp;
	int				hit_any;
	int				i;
	t_interval		range;
	int				v;

	hit_any = 0;
	i = 0;
	range = rt->t_range;
	while (i < rt->world_size)
	{
		v = rt->world[i]->hit(rt->world[i]->obj, r, range, &tmp);
		if (v)
		{
			hit_any = 1;
			range.max = tmp.t;
			*rec = tmp;
		}
		i++;
	}
	return (hit_any);
}

void	set_face_normal(t_hit_record *rec, t_ray r, t_vec3 outward_normal)
{
	if (vec3_dot(r.dir, outward_normal) < 0.0)
	{
		rec->front_face = 1;
		rec->normal = outward_normal;
	}
	else
	{
		rec->front_face = 0;
		rec->normal = vec3_neg(outward_normal);
	}
}
