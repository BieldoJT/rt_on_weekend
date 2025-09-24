#include "rt.h"


t_vec3	ambient_term(t_rt *rt, const t_hit_record *rec)
{
	t_vec3	ambient_intensity;
	t_vec3	light_out;

	ambient_intensity = vec3_mul(rt->ambient.color, rt->ambient.ratio);
	light_out = vec3_mult_vecs(ambient_intensity, rec->material->albedo);
	return (light_out);
}

int	shadow_blocked(t_rt *rt, t_vec3 p, t_vec3 to_l, double dist_l)
{
	t_ray	r;

	r = ray(p, to_l);
	return (hit_anything(rt, r, dist_l - 1e-4));
}

int	hit_anything(t_rt *rt, t_ray r, double tmax)
{
	t_hit_record	rec;
	t_interval		shadow_rng;

	interval_init(&shadow_rng, 0.001, tmax);
	return (hit_world(r, &rec, rt) != 0);
}

int	rr_terminate(t_vec3 *atten)
{
	double	probability;

	probability = atten->x;
	if (atten->y > probability)
		probability = atten->y;
	if (atten->z > probability)
		probability = atten->z;
	if (probability < 0.1)
		probability = 0.1;
	if (random_double() > probability)
		return (1);
	*atten = vec3_div(*atten, probability);
	return (0);
}
