/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:13:40 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/21 18:54:37 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		return (vec3(0.1, 0.1, 0.2)); //background color
	if (!hit_world(r, &rec, rt))
		return (vec3(0.1, 0.1, 0.2)); //background color
	if (!rec.material->scatter(rec.material, &params))
		return (rec.material->color_emited);
	return (vec3_add(rec.material->color_emited,
			vec3_mult_vecs(atten, ray_color(sctred, rt, depth - 1))));
}
