/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:33:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 17:42:00 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	center_pixel(t_camera *cam, int pixel_x, int pixel_y, t_vec3 *p_center)
{
	if (!cam || !p_center)
		return ;
	p_center->x = cam->upper_left_corner.x + (pixel_x + 0.5) * cam->pixel_du_x;
	p_center->y = cam->upper_left_corner.y - (pixel_y + 0.5) * cam->pixel_dv_y;
	p_center->z = cam->upper_left_corner.z;
}

t_vec3	get_pixel00(t_camera *camera)
{
	if (!camera)
		return (vec3(0, 0, 0));
	return (vec3_add(camera->upper_left_corner,
			vec3(camera->pixel_du_x * 0.5, camera->pixel_dv_y * 0.5, 0.0)));
}

t_vec3	get_pixel_center(t_camera *camera, int i, int j, t_vec3 pixel00)
{
	t_vec3	pixel_center;

	pixel_center = vec3_add(
			vec3_add(pixel00, vec3(camera->pixel_du_x * i, 0.0, 0.0)),
			vec3(0.0, -camera->pixel_dv_y * j, 0.0));
	return (pixel_center);
}

t_vec3	sample_square(void)
{
	double	dx;
	double	dy;

	dx = random_double() - 0.5;
	dy = random_double() - 0.5;
	return ((t_vec3){dx, dy, 0.0});
}
