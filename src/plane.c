#include "rt.h"

int	plane_hit(void *obj, t_ray r, t_interval t_range, t_hit_record *rec)
{
	t_plane	*pl;
	double	denomi;
	double	num;
	double	t;

	//plano 3d para nosso objeto plano
	pl = (t_plane *)obj;
	denomi = vec3_dot(r.dir, pl->norma);
	//se for muito proximo a 0 quer dizer que ele e paralelo ent nao bate
	if (fabs(denomi) < 1e-6)
		return (0);
	num = vec3_dot(vec3_sub(pl->point, r.orig), pl->norma);
	//descobrir a distância ao ponto de colisão
	t = num / denomi;
	//checa se a colisão está dentro da faixa de distâncias
	if (!interval_contains(&t_range, t))
		return (0);
	//Se chegou aqui, o raio realmente bateu no plano.
	//Salva a distância até a colisão.
	rec->t = t;
	//Salva o ponto exato onde bateu.
	rec->p = ray_at(r, t);
	//Salva o tipo de material (cor, brilho etc).
	rec->material = pl->material;
	//saber se estamos vendo a parte da frente ou de trás do plano
	set_face_normal(rec, r, pl->norma);
	return (1);
}

t_hittable	*plane_creat(t_vec3 point, t_vec3 norma, t_material *material)
{
	t_hittable	*ht;
	t_plane		*pl;

	ht = malloc(sizeof(*ht) + sizeof(*pl));
	if (!ht)
		return (NULL);
	//pula para o enderço de pl direto, ht + 1 pula o ht todo
	pl = (t_plane *)(ht + 1);
	//obj recebe o obj plano.
	ht->obj = pl;
	//ponto que pretence ao plano
	pl->point = point;
	//a norma do plano (direção que ele vai preencher)
	pl->norma = vec3_unit_vector(norma);
	pl->material = material;
	ht->hit = plane_hit;
	return (ht);
}