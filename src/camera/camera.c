/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:33:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/08/12 17:18:17 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	center_pixel(t_camera *cam, int pixel_x, int pixel_y, t_vec3 *p_center)
{
	if (!cam || !p_center)
		return ;
	*p_center = get_pixel_center(cam, pixel_x, pixel_y);
}

t_vec3	get_pixel00(t_camera *camera)
{
	if (!camera)
		return (vec3(0, 0, 0));
	return (vec3_add(camera->upper_left_corner,
			vec3(camera->pixel_du_x * 0.5,
				camera->pixel_dv_y * 0.5, 0.0)));
}

t_vec3	get_pixel_center(t_camera *cam, int i, int j)
{
	t_vec3	pixel_center;

	pixel_center = vec3_add(cam->upper_left_corner,
			vec3_add(vec3_mul(cam->viewport_u,
					((double)i + 0.5) / cam->img_width),
				vec3_mul(cam->viewport_v, -((double)j + 0.5)
					/ cam->img_height)));
	return (pixel_center);
}
/*
t_vec3	sample_square(void)
{
	double	dx;
	double	dy;

	dx = random_double() - 0.5;
	dy = random_double() - 0.5;
	return ((t_vec3){dx, dy, 0.0});
}
*/
