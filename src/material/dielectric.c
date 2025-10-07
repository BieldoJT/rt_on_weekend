/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:18:30 by natrodri          #+#    #+#             */
/*   Updated: 2025/09/17 10:24:58 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../ray.h"

static t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_mul(n, 2.0 * vec3_dot(v, n))));
}

/* Snell + decomposição perpendicular/paralela */
static t_vec3	refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double	cos_th;
	t_vec3	r_out_perp;
	t_vec3	r_out_parl;
	double	k;

	cos_th = fmin(vec3_dot(vec3_mul(uv, -1.0), n), 1.0);
	r_out_perp = vec3_mul(vec3_add(uv, vec3_mul(n, cos_th)), etai_over_etat);
	k = 1.0 - vec3_dot(r_out_perp, r_out_perp);
	r_out_parl = vec3_mul(n, -sqrt(fabs(k)));
	return (vec3_add(r_out_perp, r_out_parl));
}

/* Schlick (aprox. de Fresnel) */
static double	reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * pow(1.0 - cosine, 5.0));
}

static int	dielectric_scatter(const t_material *self, t_scatter_params *p)
{
	double	ref_ratio;
	t_vec3	unit_dir;
	double	cos_th;
	double	sin_th;
	int		cannot_refract;
	int		reflect_choose;
	t_vec3	dir;

	if (!self || !p || !p->r_in || !p->rec || !p->attenuation || !p->scattered)
		return (0);
	*(p->attenuation) = vec3(1.0, 1.0, 1.0);
	p->is_specular = 1;
	p->pdf = 0.0;
	ref_ratio = p->rec->front_face ? (1.0 / self->refractive_index)
		: self->refractive_index;
	unit_dir = vec3_unit_vector(p->r_in->dir);
	cos_th = fmin(vec3_dot(vec3_mul(unit_dir, -1.0), p->rec->normal), 1.0);
	sin_th = sqrt(fmax(0.0, 1.0 - cos_th * cos_th));
	cannot_refract = ref_ratio * sin_th > 1.0;
	reflect_choose = cannot_refract
		|| reflectance(cos_th, ref_ratio) > random_double();
	if (reflect_choose)
		dir = reflect(unit_dir, p->rec->normal);
	else
		dir = refract(unit_dir, p->rec->normal, ref_ratio);
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
	m->refractive_index = (refr_index <= 0.0) ? 1.0 : refr_index;
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
