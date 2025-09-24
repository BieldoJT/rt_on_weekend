#include "rt.h"

t_point_light	*point_light_create(t_vec3 position, double intensity, t_vec3 color)
{
	t_point_light	*light;

	light = malloc(sizeof(t_point_light));
	if (!light)
		return (NULL);
	light->position = position;
	light->intensity = vec3_mul(color, intensity);
	light->next = NULL;
	return (light);
}

void	point_light_destroy(t_point_light **light)
{
	t_point_light	*next;

	while(*light)
	{
		next = (*light)->next;
		free(*light);
		*light = next;
	}
	*light = NULL;
}

void	point_light_add(t_point_light **lights, t_point_light *new_light)
{
	t_point_light	*current;

	if (!lights || !new_light)
		return ;
	if (!*lights)
	{
		*lights = new_light;
	}
	else
	{
		current = *lights;
		while (current->next)
			current = current->next;
		current->next = new_light;
	}
}

t_vec3	point_light_diffuse(t_rt *rt, const t_hit_record *rec, t_point_light *light)
{
	t_vec3	lo;
	t_vec3	nl;
	double	dist;
	double	n_dot_l;
	t_vec3	c;

	lo = vec3_sub(light->position, rec->p);
	dist = vec3_length(lo);
	if (dist <= 0.0)
		return (vec3(0, 0, 0));
	nl = vec3_unit_vector(lo);
	if (shadow_blocked(rt, rec->p, nl, dist))
		return (vec3(0, 0, 0));
	n_dot_l = vec3_dot(rec->normal, nl);
	if (n_dot_l <= 0.0)
		return (vec3(0, 0, 0));
	c = vec3_div(light->intensity, (dist * dist));
	return (vec3_mul(vec3_mult_vecs(rec->material->albedo, c), n_dot_l));
}
