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

#include "rt.h"

void    set_ambient(t_rt *rt, double ratio, t_vec3 color)
{
    rt->ambient.ratio = ratio;
    rt->ambient.color = color;
}

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
	rt->image_width = 1000;
	rt->image_height = (int)(rt->image_width / aspect_ratio);
	rt->mlx = malloc(sizeof(t_mlx));
	if (rt->image_height < 1)
		rt->image_height = 1;
	init_mlx(rt);
	rt->camera = init_camera(aspect_ratio, rt->image_width, rt->image_height);
	rt->camera->count_samples = 0;
	rt->camera->sample_per_pixel = 500;
	rt->camera->pixel_sample_scale = 1.0 / rt->camera->sample_per_pixel;
	rt->camera->max_depth = 20;
	set_ambient(rt, 0.8, vec3(1.0, 1.0, 1.0));
	create_world(rt);
}

static void	create_world(t_rt *rt)
{
	rt->world = malloc(sizeof(t_hittable *) * 20);
	if (!rt->world)
		return ;
	rt->world[rt->world_size++] = sphere_create(vec3(0.0, -100.5, -1.0), 100.0,
			lambertian_create(vec3(0.8, 0.2, 0.3)));
	double ra_and_he[2];
    ra_and_he[0] = 0.3;  // raio
    ra_and_he[1] = 1.0;  // altura

    rt->world[rt->world_size++] = cylinder_create(
        vec3(0.0, 0.0, -1.2), // posição (troquei a Y para 0.0 pra ficar no chão)
        vec3(0, 1, 0),        // direção (eixo y, para cima)
        ra_and_he,
        lambertian_create(vec3(1, 1, 1)) // material branco difuso
    );
	/*rt->world[rt->world_size++] = sphere_create(vec3(0.0, 0.5, -1.2), 0.5,
			metal_create(vec3(1, 1, 1), 0.01));*/
	/*rt->world[rt->world_size++] = sphere_create(vec3(1.0, 0.0, -1.0), 0.5,
			dielectric_create(2.8));*/
	rt->n_lights = 2;
 rt->lights = malloc(sizeof(t_point_light *) * rt->n_lights);
if (rt->lights)
    rt->lights[0] = point_light_create(vec3(-2.0, 1.0, 0.0), vec3(0.0, 0.0, 255.0));
	rt->lights[1] = point_light_create(vec3(2.0, 1.0, 0.0), vec3(0.0, 255.0, 0.0));
	// rt->lights[1] = point_light_create(vec3(-2.5, 4.0, 0.5), vec3(50.0, 50.0, 250.0));
	/*rt->n_lights = 1;
	rt->lights = malloc(sizeof(t_point_light *) * rt->n_lights);
	rt->lights[0] = point_light_create(vec3(-1.5, 4, 0.5), vec3(5, 5, 5));*/
}
