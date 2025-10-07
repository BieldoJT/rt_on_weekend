#include "rt.h"

t_point_light	*point_light_create(t_vec3 position, t_vec3 intensity)
{
	t_point_light	*light;

	light = malloc(sizeof(t_point_light));
	if (!light)
		return (NULL);
	light->position = position;
	light->intensity = intensity;
	return (light);
}
