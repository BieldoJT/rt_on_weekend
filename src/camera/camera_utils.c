/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:40:16 by natrodri          #+#    #+#             */
/*   Updated: 2025/08/12 17:23:55 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_camera	*init_camera(double aspect_ratio, int image_width, int image_height)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->camera_center = vec3(0, 0, 0);
	cam->focal_length = 1.0;
	cam->viewport_height = 2.0;
	cam->viewport_width = cam->viewport_height * aspect_ratio;
	cam->viewport_u = vec3(cam->viewport_width / 2, 0, 0);
	cam->viewport_v = vec3(0, cam->viewport_height / 2, 0);
	cam->pixel_du_x = cam->viewport_width / (double)image_width;
	cam->pixel_dv_y = cam->viewport_height / (double)image_height;
	cam->upper_left_corner = vec3(-cam->viewport_u.x,
			cam->viewport_v.y, -cam->focal_length);
	cam->sample_per_pixel = 600;
	cam->pixel_sample_scale = 1.0 / cam->sample_per_pixel;
	cam->max_depth = 50;
	cam->background_color = vec3(0.5, 0.7, 1.0);
	return (cam);
}

void	destroy_camera(t_camera *camera)
{
	if (camera)
	{
		free(camera);
	}
}

static t_vec3	sample_stratified(int s, int n)
{
	int		sample_x;
	int		sample_y;
	double	dx;
	double	dy;

	sample_x = s % n;
	sample_y = s / n;
	//random moviment
	dx = ((double)sample_x + random_double()) / (double)n - 0.5;
	dy = ((double)sample_y + random_double()) / (double)n - 0.5;
	return ((t_vec3){dx, dy, 0.0});
}

/*
** Constrói um raio que parte de cam->camera_center e atravessa
** o pixel (i,j), com jitter dentro do pixel.
** get_ray_stratified
*/
t_ray	get_ray(const t_camera *cam, int i, int j, int *sample_index)
{
	t_vec3	offset;
	double	u;
	double	v;
	t_vec3	pixel_sample;

	offset = sample_stratified(sample_index[0], sample_index[1]);
	u = ((double)i + offset.x) * cam->pixel_du_x;
	v = ((double)j + offset.y) * cam->pixel_dv_y;
	pixel_sample = vec3_add(vec3_add(cam->upper_left_corner,
				vec3(u, 0.0, 0.0)), vec3(0.0, -v, 0.0));
	return (ray(cam->camera_center,
			vec3_sub(pixel_sample, cam->camera_center)));
}
