/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/09/01 14:41:18 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_world(t_rt *rt);

void	init_rt(t_rt *rt)
{
	double	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	rt->mlx = NULL;
	rt->world_size = 0;
	rt->t_range = (t_interval){0, 0};
	rt->intensity = (t_interval){0, 0};
	interval_init(&rt->t_range, 0.001, INFINITY);
	interval_init(&rt->intensity, 0.000, 0.999);
	rt->image_width = 400;
	rt->image_height = (int)(rt->image_width / aspect_ratio);
	rt->mlx = malloc(sizeof(t_mlx));
	if (rt->image_height < 1)
		rt->image_height = 1;
	init_mlx(rt);
	rt->camera = init_camera(aspect_ratio, rt->image_width, rt->image_height);
	rt->camera->count_samples = 0;
	rt->camera->sample_per_pixel = 128;  //final 128 , preview 64
	rt->camera->pixel_sample_scale = 1.0 / rt->camera->sample_per_pixel;
	rt->camera->max_depth = 20; //final 20 , preview 12
	create_world(rt);
}

static void	create_world(t_rt *rt)
{
	rt->world = malloc(sizeof(t_hittable *) * 20);
	if (!rt->world)
		return ;
	rt->world[rt->world_size++] = sphere_create(vec3(0.0, -100.5, -1.0), 100.0,
			lambertian_create(vec3(0.8, 0.2, 0.3)));
	rt->world[rt->world_size++] = sphere_create(vec3(0.0, 0.0, -1.2), 0.5,
			lambertian_create(vec3(0.1, 0.8, 4.0)));
	rt->world[rt->world_size++] = sphere_create(vec3(-1.0, 0.0, -1.0), 0.5,
			metal_create(vec3(0.8, 0.6, 0.2), 0.1));
	rt->world[rt->world_size++] = sphere_create(vec3(1.0, 0.0, -1.0), 0.5,
			dielectric_create(1.8));
	rt->world[rt->world_size++] = sphere_create(vec3(-1.5, 1.0, 0.5), 0.5,
			diffuse_light_create(vec3(10.0, 10.0, 10.0)));
	/*
	int i = 5;
	float aaa = 0.2;
	while (i < 20)
	{
		rt->world[rt->world_size++] = sphere_create(vec3(0.0, aaa, -1.0 + (aaa * -1)), 0.5,
				lambertian_create(vec3(0.5 * (i % 2), 0.5 * (i % 3), 0.5 * (i % 4))));
		i++;
		aaa += 0.2;
	}
	*/
}
