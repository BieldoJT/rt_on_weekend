/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/09/26 17:16:33 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	set_ambient(t_rt *rt, double ratio, t_vec3 color)
{
	rt->ambient.ratio = ratio;
	rt->ambient.color = color;
}

static void	create_world(t_rt *rt, t_scene *scene);

void	init_rt(t_rt *rt, t_scene *scene)
{
	double	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	rt->mlx = NULL;
	rt->world_size = 0;
	rt->t_range = (t_interval){0, 0};
	rt->intensity = (t_interval){0, 0};
	interval_init(&rt->t_range, 0.001, INFINITY);
	interval_init(&rt->intensity, 0.000, 0.999);
	rt->image_width = 1000;
	rt->image_height = (int)(rt->image_width / aspect_ratio);
	if (rt->image_height < 1)
		rt->image_height = 1;
	rt->mlx = malloc(sizeof(t_mlx));
	init_mlx(rt);
	rt->camera = init_camera(&scene->camera, aspect_ratio, rt->image_width,
			rt->image_height);
	rt->camera->count_samples = 0;
	rt->camera->sample_per_pixel = 500;
	rt->camera->pixel_sample_scale = 1.0 / rt->camera->sample_per_pixel;
	rt->camera->max_depth = 20;
	set_ambient(rt, 0.8, vec3(1.0, 1.0, 1.0));
	create_world(rt, scene);
}

static void	create_world(t_rt *rt, t_scene *scene)
{
	rt->world_size = 0;
	rt->world = malloc(sizeof(t_hittable *) * 20);
	if (!rt->world)
		return ;
	if (scene->spheres)
		add_sphere(scene->spheres, rt);
	if (scene->planes)
		add_plane(scene->planes, rt);
	if (scene->cylinders)
		add_cylinder(scene->cylinders, rt);
	if (scene->lights)
		add_lights(scene->lights, rt);
}
