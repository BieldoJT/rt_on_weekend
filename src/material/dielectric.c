/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:18:30 by natrodri          #+#    #+#             */
/*   Updated: 2025/10/02 11:49:24 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../ray.h"

static t_vec3	get_scatter_dir(t_vec3 unit_dir, const t_hit_record *rec,
					double ref_ratio, double cos_th)
{
	double	sin_th;
	int		cannot_refract;
	int		reflect_choose;
	int		tmp;

	sin_th = sqrt(fmax(0.0, 1.0 - cos_th * cos_th));
	cannot_refract = ref_ratio * sin_th > 1.0;
	tmp = reflectance(cos_th, ref_ratio);
	reflect_choose = (cannot_refract || tmp > random_double());
	if (reflect_choose)
		return (reflect(unit_dir, rec->normal));
	return (refract(unit_dir, rec->normal, ref_ratio));
}

int	dielectric_scatter(const t_material *self, t_scatter_params *p)
{
	double	ref_ratio;
	t_vec3	unit_dir;
	double	cos_th;
	t_vec3	dir;

	if (!self || !p || !p->r_in || !p->rec
		|| !p->attenuation || !p->scattered)
		return (0);
	*(p->attenuation) = vec3(1.0, 1.0, 1.0);
	p->is_specular = 1;
	p->pdf = 0.0;
	if (p->rec->front_face == 1)
		ref_ratio = 1.0 / self->refractive_index;
	else
		ref_ratio = self->refractive_index;
	unit_dir = vec3_unit_vector(p->r_in->dir);
	cos_th = fmin(vec3_dot(vec3_mul(unit_dir, -1.0), p->rec->normal), 1.0);
	dir = get_scatter_dir(unit_dir, p->rec, ref_ratio, cos_th);
	*(p->scattered) = ray(p->rec->p, dir);
	return (1);
}

static double	dielectric_scattering_pdf(const t_material *mat,
				const t_ray *r_in, const t_hit_record *rec, t_vec3 *scattered)
{
	(void)mat;
	(void)r_in;
	(void)rec;
	(void)scattered;
	return (0.0);
}

void	material_set_dielectric(t_material *m, double refr_index)
{
	if (!m)
		return ;
	m->scatter = &dielectric_scatter;
	m->scattering_pdf = &dielectric_scattering_pdf;
	m->albedo = vec3(1.0, 1.0, 1.0);
	m->fuzz = 0.0;
	if (refr_index <= 0.0)
		m->refractive_index = 1.0;
	else
		m->refractive_index = refr_index;
	m->color_emited = vec3(0.0, 0.0, 0.0);
}

t_material	*dielectric_create(double refr_index)
{
	t_material	*m;

	m = (t_material *)malloc(sizeof(*m));
	if (!m)
		return (NULL);
	material_set_dielectric(m, refr_index);
	return (m);
}
