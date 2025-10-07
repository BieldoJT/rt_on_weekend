/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:18:36 by natrodri          #+#    #+#             */
/*   Updated: 2025/09/24 02:12:35 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../ray.h"

static int	lambertian_scatter(const t_material *self, t_scatter_params *p)
{
	if (!self || !p || !p->attenuation)
		return (0);
	*(p->attenuation) = self->albedo;
	p->is_specular = 0;
	p->pdf = 1.0;
	return (1);
}

/*
** PDF de espalhamento do Lambert:
**   pdf = cos(theta) / PI     (0 se cos < 0)
** theta = ângulo entre normal e direção 'scattered' (vetor mundo)
*/
double	lambertian_scattering_pdf(const t_material *mat, const t_ray *r_in,
			const t_hit_record *rec, t_vec3 *scattered)
{
	t_vec3	w;
	double	cos_theta;

	(void)mat;
	(void)r_in;
	if (!rec || !scattered)
		return (0.0);
	w = vec3_unit_vector(*scattered);
	cos_theta = vec3_dot(rec->normal, w);
	if (cos_theta <= 0.0)
		return (0.0);
	return (cos_theta / PI);
}

/*
** Emissão do Lambert: zero (não emite).
** (mantemos para conveniência, já que seu t_material não tem emitted_fn)
*/
t_vec3	lambertian_emitted(const t_material *mat, const t_hit_record *rec,
			double u, double v, t_vec3 p)
{
	(void)mat;
	(void)rec;
	(void)u;
	(void)v;
	(void)p;
	return (vec3(0.0, 0.0, 0.0));
}

/*
** Setter do material lambertiano:
** - define albedo e zera campos não usados
** - conecta scatter e scattering_pdf
** - emitted fica implícito (usar color_emited == 0 para não-emissivo)
*/
void	material_set_lambertian(t_material *mat, t_vec3 albedo)
{
	if (!mat)
		return ;
	mat->scatter = &lambertian_scatter;
	mat->scattering_pdf = &lambertian_scattering_pdf;
	mat->albedo = albedo;
	mat->fuzz = 0.2;
	mat->refractive_index = 1.0;
	mat->color_emited = vec3(0.0, 0.0, 0.0);
}


/* -------- (opcional) se você usa padrão create/aloca ---------- */

t_material	*lambertian_create(t_vec3 albedo)
{
	t_material	*m;

	m = (t_material *)malloc(sizeof(*m));
	if (!m)
		return (NULL);
	material_set_lambertian(m, albedo);
	return (m);
}
