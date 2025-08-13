/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:13:40 by gda-conc          #+#    #+#             */
/*   Updated: 2025/08/12 20:04:10 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int rr_terminate(t_vec3 *atten)
{
	double  probability;

	/* prob. de sobrevivência baseada no maior canal da atenuação (clamp) */
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

t_vec3	ray_color(t_ray r, t_rt *rt, int depth)
{
	t_hit_record		rec;
	t_scatter_params	params;
	t_vec3				atten;
	t_ray				sctred;

	params.r_in = &r;
	params.rec = &rec;
	params.attenuation = &atten;
	params.scattered = &sctred;
	if (depth <= 0)
		return (vec3(0.0, 0.0, 0.0)); //background color (vec3(0.1, 0.1, 0.2));
	if (!hit_world(r, &rec, rt))
		return (vec3(0.0, 0.0, 0.0)); //background color (vec3(0.1, 0.1, 0.2));
	if (!rec.material->scatter(rec.material, &params))
		return (rec.material->color_emited);
	if (depth <= 5 && rr_terminate(&atten))
		return (rec.material->color_emited);
	return (vec3_add(rec.material->color_emited,
			vec3_mult_vecs(atten, ray_color(sctred, rt, depth - 1))));
}
