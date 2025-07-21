/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   difuse_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:18:33 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 17:18:56 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../ray.h"

static int	diffuse_light_scatter(const t_material *self, t_scatter_params *p)
{
	*p->attenuation = self->albedo;
	*p->scattered = ray(p->rec->p, random_unit_vector());
	return (0);
}

t_material	*diffuse_light_create(t_vec3 albedo)
{
	t_material	*m;

	m = malloc(sizeof(*m));
	if (!m)
		return (NULL);
	m->scatter = diffuse_light_scatter;
	m->albedo = albedo;
	m->fuzz = 0.0;
	m->refractive_index = 1.0;
	m->color_emited = albedo;
	return (m);
}

/* ================ Destrutor ================= */
void	material_destroy(t_material *m)
{
	free(m);
}
