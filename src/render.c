/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:17:55 by gda-conc          #+#    #+#             */
/*   Updated: 2025/08/12 18:03:26 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	degree_to_radian(double degree)
{
	double	pi;

	pi = 3.1415926535897932385;
	return (degree * (pi / 180.0));
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

double	linear_to_gamma(double x)
{
	if (x > 0)
		return (sqrt(x));
	return (0.0);
}


//COM ANTI-ALIASING
int	anti_aliasing_get_color(t_rt *rt, int i, int j)
{
	t_vec3	pixel_color;
	t_ray	r;
	t_vec3	irgb;
	int		sample_index[2]; //to have the 2 variables

	pixel_color = vec3(0, 0, 0);
	sample_index[1] = (int)sqrt((float)rt->camera->sample_per_pixel);
	if (sample_index[1] < 1) sample_index[1] = 1;
	sample_index[0] = 0;
	while (sample_index[0] < sample_index[1] * sample_index[1])
	{
		r = get_ray(rt->camera, i, j, sample_index);
		pixel_color = vec3_add(pixel_color,
				ray_color(r, rt, rt->camera->max_depth));
		sample_index[0]++;
	}
	pixel_color = vec3_mul(pixel_color, rt->camera->pixel_sample_scale);
	pixel_color.x = linear_to_gamma(pixel_color.x);
	pixel_color.y = linear_to_gamma(pixel_color.y);
	pixel_color.z = linear_to_gamma(pixel_color.z);
	irgb.x = (int)(256 * interval_clamp(&rt->intensity, pixel_color.x));
	irgb.y = (int)(256 * interval_clamp(&rt->intensity, pixel_color.y));
	irgb.z = (int)(256 * interval_clamp(&rt->intensity, pixel_color.z));
	return (rgb_to_int(irgb.x, irgb.y, irgb.z));
}

void	render_rt(t_rt *rt)
{
	int		i;
	int		j;
	t_mlx	*mlx;
	int		packed_color;

	mlx = rt->mlx;
	ft_printf("Rendering image...\n");
	j = 0;
	while (j < rt->image_height)
	{
		ft_printf("\rScanlines remaining: %d ", rt->image_height - j);
		i = 0;
		while (i < rt->image_width)
		{
			packed_color = anti_aliasing_get_color(rt, i, j);
			my_mlx_pixel_put(rt->mlx, i, j, packed_color);
			i++;
		}
		j++;
	}
	ft_printf("\nDone.\n");
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	mlx_key_hook(mlx->win_ptr, destroy_in_esc, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, destroy, mlx);
	mlx_loop(mlx->mlx_ptr);
}
