/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/10/03 18:00:34 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include <pthread.h>

#ifndef NTHREADS
# define NTHREADS 12
#endif

int	anti_aliasing_get_color(t_rt *rt, int i, int j)
{
	t_vec3	pixel_color;
	t_ray	r;
	t_vec3	irgb;
	int		sample_index[2];

	pixel_color = vec3(0, 0, 0);
	sample_index[1] = (int)sqrt((float)rt->camera->count_samples);
	if (sample_index[1] < 1)
		sample_index[1] = 1;
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

static void	*rt_worker(void *arg)
{
	t_job	*job;
	int		j;
	int		i;

	job = (t_job *)arg;
	j = job->y0;
	while (j < job->y1)
	{
		i = 0;
		while (i < job->rt->image_width)
		{
			job->rt->image_index[j][i] = anti_aliasing_get_color(job->rt, i, j);
			i++;
		}
		j++;
	}
	return (NULL);
}

static void	render_parallel(t_rt *rt)
{
	pthread_t	th[NTHREADS];
	t_job		jobs[NTHREADS];
	int			hty[3];
	int			step;

	hty[0] = rt->image_height;
	step = (hty[0] + NTHREADS - 1) / NTHREADS;
	hty[1] = 0;
	while (hty[1] < NTHREADS)
	{
		hty[2] = hty[1] * step;
		jobs[hty[1]].rt = rt;
		jobs[hty[1]].y0 = hty[2];
		jobs[hty[1]].y1 = hty[2] + step;
		if (jobs[hty[1]].y1 > hty[0])
			jobs[hty[1]].y1 = hty[0];
		if (pthread_create(&th[hty[1]], NULL, rt_worker, &jobs[hty[1]]) != 0)
			ft_printf("warn: pthread_create falhou no t=%d\n", hty[1]);
		hty[1]++;
	}
	while (hty[1]--)
		pthread_join(th[hty[1]], NULL);
	int_to_img(rt);
	mlx_put_image_to_window(rt->mlx->mlx_ptr,
		rt->mlx->win_ptr, rt->mlx->img, 0, 0);
}

int	render_loop(t_rt *rt)
{
	if (rt->camera->count_samples >= rt->camera->sample_per_pixel)
	{
		ft_printf("Rendering complete.\r");
		return (0);
	}
	if (rt->camera->count_samples < rt->camera->sample_per_pixel)
	{
		render_parallel(rt);
		int_to_img(rt);
		mlx_put_image_to_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr,
			rt->mlx->img, 0, 0);
		rt->camera->count_samples++;
		ft_printf("Rendering... %d samples per pixel.\r",
			rt->camera->count_samples);
	}
	return (0);
}

void	render_rt(t_rt *rt, t_scene *scene)
{
	t_mlx	*mlx;

	mlx = rt->mlx;
	mlx->scene = scene;
	ft_printf("Rendering image (multithread)...\n");
	mlx_loop_hook(mlx->mlx_ptr, render_loop, rt);
	mlx_key_hook(mlx->win_ptr, destroy_in_esc, rt);
	mlx_hook(mlx->win_ptr, 17, 0, destroy, rt);
	mlx_loop(mlx->mlx_ptr);
}
