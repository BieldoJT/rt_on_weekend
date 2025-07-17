#ifndef HITTABLE_H
# define HITTABLE_H
# include "vec3.h"
# include "rt.h"
# include "ray.h"
# include "interval.h"
# include "material.h"

typedef struct s_material  t_material;



typedef struct s_hit_record
{
	double t;          // parâmetro t do raio
	t_vec3 p;         // ponto de interseção
	t_vec3 normal;    // normal na interseção
	double u; // coordenada u da textura
	double v; // coordenada v da textura
	t_material *material; // material do objeto atingido
	int front_face;   // se a face normal está voltada para o raio

} t_hit_record;

typedef struct s_hittable
{
	void *obj; // ponteiro para o objeto (ex: esfera)
	int (*hit)(void *object,
		t_ray r,
		double t_min,
		double t_max,
		t_hit_record *rec);
} t_hittable;

int		hit_world(t_ray r, t_hit_record *rec, t_rt *rt);
void	set_face_normal(t_hit_record *rec, t_ray r, t_vec3 outward_normal);


#endif
