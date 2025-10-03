#include "rt.h"

void	free_index(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->image_height)
	{
		free(rt->image_index[i]);
		i++;
	}
	free(rt->image_index);
}

void free_create_lights(t_rt *rt)
{
	t_point_light **lights = rt->lights;
	int i = 0;

	if (!rt->n_lights)
		return ;
	while (i < rt->n_lights)
	{

		free(lights[i]);
		i++;
	}
	free(lights);
}

void free_world(t_rt *rt)
{
    int	i;

    i = 0;
    if (!rt->world)
        return ;
    while (i < rt->world_size)
    {
		if(rt->world[i]->type == 'c')
			free(rt->world[i]->obj);
		free(rt->world[i]->material);
        free(rt->world[i]);
        i++;
    }
    free(rt->world);
}
