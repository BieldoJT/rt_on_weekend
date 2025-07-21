/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:40:16 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 17:45:44 by natrodri         ###   ########.fr       */
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

/*
** Constrói um raio que parte de cam->camera_center e atravessa
** o pixel (i,j), com jitter dentro do pixel.
*/
t_ray	get_ray(const t_camera *cam, int i, int j)
{
	t_vec3	offset;
	double	u;
	double	v;
	t_vec3	pixel_sample;

	offset = sample_square();
	u = ((double)i + offset.x) * cam->pixel_du_x;
	v = ((double)j + offset.y) * cam->pixel_dv_y;
	pixel_sample = vec3_add(vec3_add(cam->upper_left_corner,
				vec3(u, 0.0, 0.0)), vec3(0.0, -v, 0.0));
	return (ray(cam->camera_center,
			vec3_sub(pixel_sample, cam->camera_center)));
}
