#include "../rt.h"
#include "../ray.h"

static double	reflectance(double cos, double refr_index)
{
	double	r0;

	r0 = (1 - refr_index) / (1 + refr_index);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cos), 5));
}

static void	direction_dielectric(t_scatter_params *p,
									double ri, t_vec3 *direction)
{
	t_vec3	unit_direction;
	double	cos_theta;
	double	sin_theta;
	int		cannot_refract;

	unit_direction = vec3_unit_vector(p->r_in->dir);
	cos_theta = fmin(vec3_dot(vec3_neg(unit_direction), p->rec->normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	cannot_refract = ri * sin_theta > 1.0;
	if (cannot_refract || reflectance(cos_theta, ri) > random_double())
		*direction = vec3_reflect(unit_direction, p->rec->normal);
	else
		*direction = vec3_refract(unit_direction, p->rec->normal, ri);
}

static int	dielectric_scatter(const t_material *self, t_scatter_params *p)
{
	double	ri;
	t_vec3	direction;

	*p->attenuation = self->albedo;
	if (p->rec->front_face)
		ri = 1.0 / self->refractive_index;
	else
		ri = self->refractive_index;
	direction_dielectric(p, ri, &direction);
	*p->scattered = ray(p->rec->p, direction);
	return (1);
}

t_material	*dielectric_create(double refractive_index)
{
	t_material	*m;

	m = malloc(sizeof(*m));
	if (!m)
		return (NULL);
	m->scatter = dielectric_scatter;
	m->albedo = vec3(1.0, 1.0, 1.0);
	m->fuzz = 0.0;
	m->refractive_index = refractive_index;
	m->color_emited = vec3(0.0, 0.0, 0.0);
	return (m);
}