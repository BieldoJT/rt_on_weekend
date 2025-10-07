/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/09/26 17:16:33 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static t_vec3	calc_direct_light(t_rt *rt, t_hit_record *hit)
{
	int		li;
	t_vec3	direct;

	direct = vec3(0.0, 0.0, 0.0);
	li = 0;
	while (li < rt->n_lights)
	{
		direct = vec3_add(direct, point_light_diffuse(rt, hit, li));
		li++;
	}
	return (direct);
}

static t_vec3	handle_scatter(t_trace_data *td, t_rt *rt, int depth,
		t_vec3 amb)
{
	t_vec3	direct;

	direct = calc_direct_light(rt, &td->hit);
	if (td->scatter_params.is_specular)
		return (vec3_add(amb,
				vec3_add(td->emission,
					vec3_mult_vecs(td->atten,
						vec3_add(direct,
							ray_color(td->ray_next, rt, depth - 1))))));
	return (vec3_add(amb,
			vec3_add(td->emission,
				vec3_mult_vecs(td->atten, direct))));
}

t_vec3	ray_color(t_ray r, t_rt *rt, int depth)
{
	t_trace_data	td;
	t_vec3			amb;

	td.scatter_params.r_in = &r;
	td.scatter_params.rec = &td.hit;
	td.scatter_params.attenuation = &td.atten;
	td.scatter_params.scattered = &td.ray_next;
	td.scatter_params.is_specular = 0;
	td.scatter_params.pdf = 0.0;
	if (depth <= 0)
		return (vec3(0, 0, 0));
	if (!hit_world(r, &td.hit, rt))
		return (vec3(0, 0, 0));
	td.emission = td.hit.material->color_emited;
	if (!td.hit.material->scatter(td.hit.material, &td.scatter_params))
		return (td.emission);
	if (depth <= 5 && rr_terminate(&td.atten))
		return (td.emission);
	amb = ambient_term(rt, &td.hit);
	return (handle_scatter(&td, rt, depth, amb));
}
