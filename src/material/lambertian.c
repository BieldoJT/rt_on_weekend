#include "../rt.h"
#include "../ray.h"

static int	lambertian_scatter(const t_material *self, t_scatter_params *p)
{
	t_vec3	dir;

	(void)p->r_in;
	dir = vec3_add(p->rec->normal, random_unit_vector());
	if (vec3_near_zero(dir))
		dir = p->rec->normal;
	*p->scattered = ray(p->rec->p, dir);
	*p->attenuation = self->albedo;
	return (1);
}

t_material	*lambertian_create(t_vec3 albedo)
{
	t_material	*m;

	m = malloc(sizeof(*m));
	if (!m)
		return (NULL);
	m->scatter = lambertian_scatter;
	m->albedo = albedo;
	m->fuzz = 0.0;
	m->refractive_index = 1.0;
	m->color_emited = vec3(0.0, 0.0, 0.0);
	return (m);
}