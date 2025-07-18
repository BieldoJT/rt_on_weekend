#ifndef RAY_H
# define RAY_H

# include "vec3/vec3.h"

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

// Constrói um raio dado origem e direção
t_ray	ray(t_vec3 origin, t_vec3 direction);

// Retorna a origem do raio

t_vec3	ray_origin(t_ray r);

// Retorna a direção do raio
t_vec3	ray_direction(t_ray r);

// Retorna o ponto em r(t) = orig + t*dir
t_vec3	ray_at(t_ray r, double t);


#endif
