/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:18:39 by natrodri          #+#    #+#             */
/*   Updated: 2025/09/17 10:26:05 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../ray.h"

static t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_mul(n, 2.0 * vec3_dot(v, n))));
}

static int	metal_scatter(const t_material *self, t_scatter_params *p)
{
	t_vec3	unit_in;
	t_vec3	reflected;
	t_vec3	dir;

	if (!self || !p || !p->r_in || !p->rec || !p->attenuation || !p->scattered)
		return (0);
	unit_in = vec3_unit_vector(p->r_in->dir);
	reflected = reflect(unit_in, p->rec->normal);
	dir = vec3_add(reflected,
			vec3_mul(random_unit_vector(), fmin(fabs(self->fuzz), 1.0)));
	if (vec3_near_zero(dir))
		dir = reflected;
	*(p->scattered) = ray(p->rec->p, dir);
	*(p->attenuation) = self->albedo;
	p->is_specular = 1;
	p->pdf = 0.0;
	return (vec3_dot(dir, p->rec->normal) > 0.0);
}

static double	metal_scattering_pdf(const t_material *mat, const t_ray *r_in,
				const t_hit_record *rec, t_vec3 *scattered)
{
	(void)mat;
	(void)r_in;
	(void)rec;
	(void)scattered;
	return (0.0);
}

void	material_set_metal(t_material *m, t_vec3 albedo, double fuzz)
{
	if (!m)
		return ;
	m->scatter = &metal_scatter;
	m->scattering_pdf = &metal_scattering_pdf;
	m->albedo = albedo;
	m->fuzz = (fuzz < 0.0) ? 0.0 : ((fuzz > 1.0) ? 1.0 : fuzz);
	m->refractive_index = 1.0;
	m->color_emited = vec3(0.0, 0.0, 0.0);
}

t_material	*metal_create(t_vec3 albedo, double fuzz)
{
	t_material	*m;

	m = (t_material *)malloc(sizeof(*m));
	if (!m)
		return (NULL);
	material_set_metal(m, albedo, fuzz);
	return (m);
}
