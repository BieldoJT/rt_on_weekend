/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:18:39 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 17:18:49 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../ray.h"

static int	metal_scatter(const t_material *self, t_scatter_params *p)
{
	t_vec3	reflected;

	reflected = vec3_reflect(p->r_in->dir, p->rec->normal);
	reflected = vec3_add(vec3_unit_vector(reflected),
			vec3_mul(random_unit_vector(), self->fuzz));
	*p->scattered = ray(p->rec->p, reflected);
	*p->attenuation = self->albedo;
	return (vec3_dot(p->scattered->dir, p->rec->normal) > 0.0);
}

t_material	*metal_create(t_vec3 albedo, double fuzz)
{
	t_material	*m;

	m = malloc(sizeof(*m));
	if (!m)
		return (NULL);
	m->scatter = metal_scatter;
	m->albedo = albedo;
	if (fuzz < 1.0)
		m->fuzz = fuzz;
	else
		m->fuzz = 1.0;
	m->refractive_index = 1.0;
	m->color_emited = vec3(0.0, 0.0, 0.0);
	return (m);
}
