#include "ray.h"
#include "rt.h"

//cria um raio com origem e direção
t_ray ray(t_vec3 origin, t_vec3 direction)
{
	t_ray r;

	r.orig = origin;
	r.dir = direction;
	return r;
}

//acessor para a origem do raio
t_vec3 ray_origin(t_ray r)
{
	return r.orig;
}

//acessor para a direção do raio
t_vec3 ray_direction(t_ray r)
{
	return r.dir;
}

//retorna o ponto no raio dado um parâmetro t
t_vec3 ray_at(t_ray r, double t)
{
	return vec3_add(r.orig, vec3_mul(r.dir, t));
}


