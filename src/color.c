/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:13:40 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/18 18:37:48 by natrodri         ###   ########.fr       */
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
		return (vec3(0, 0, 0));
	if (!hit_world(r, &rec, rt))
		return (vec3(0, 0, 0));
	if (!rec.material->scatter(rec.material, &params))
		return (rec.material->color_emited);
	return (vec3_add(rec.material->color_emited,
			vec3_mult_vecs(atten, ray_color(sctred, rt, depth - 1))));
}
