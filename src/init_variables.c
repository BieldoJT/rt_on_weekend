/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/25 12:04:11 by natrodri         ###   ########.fr       */
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
	rt->camera->sample_per_pixel = 1000;
	rt->camera->pixel_sample_scale = 1.0 / rt->camera->sample_per_pixel;
	rt->camera->max_depth = 50;
	create_world(rt);
}

static void create_world(t_rt *rt)
{
    rt->world = malloc(sizeof(t_hittable *) * 5);
    if (!rt->world)
        return ;
    rt->world[rt->world_size++] = plane_creat(vec3(0, -0.5, 0), vec3(0, 1, 0),
		lambertian_create(vec3(0.2, 0.8, 0.2)));
    rt->world[rt->world_size++] = sphere_create(vec3(0.0, 0.0, -1.2), 0.5,
		metal_create(vec3(0., 0.2, 0.5), 0.5));
}
