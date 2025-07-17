#ifndef SPHERE_H
# define SPHERE_H

# include "rt.h"
# include "hittable.h"
# include "material.h"

# define PI 3.14159

typedef struct s_sphere
{
	t_vec3 center; // centro da esfera
	double radius; // raio da esfera
	t_material *material; // material da esfera (opcional)

} t_sphere;

t_hittable *sphere_create(t_vec3 center, double radius, t_material *material);
void sphere_destroy(t_hittable *hittable);
int sphere_hit(void *object, t_ray r, double t_min, double t_max, t_hit_record *rec);

#endif
