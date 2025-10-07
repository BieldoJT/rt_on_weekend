 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:17:55 by gda-conc          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:48 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <pthread.h>

#ifndef NTHREADS
# define NTHREADS 12
#endif

typedef struct s_job
{
	t_rt	*rt;
	int		y0;
	int		y1;
}	t_job;

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
	sample_index[1] = (int)sqrt((float)rt->camera->count_samples);
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

static void	*rt_worker(void *arg)
{
	t_job	*job;
	int		j;
	int		i;
	int		color;

	job = (t_job *)arg;
	j = job->y0;
	while (j < job->y1)
	{
		i = 0;
		while (i < job->rt->image_width)
		{
			color = anti_aliasing_get_color(job->rt, i, j);
			my_mlx_pixel_put(job->rt->mlx, i, j, color);
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
	int			h;
	int			step;
	int			t;
	int			y;

	h = rt->image_height;
	step = (h + NTHREADS - 1) / NTHREADS;
	t = 0;
	while (t < NTHREADS)
	{
		y = t * step;
		jobs[t].rt = rt;
		jobs[t].y0 = y;
		jobs[t].y1 = (y + step > h) ? h : (y + step);
		if (pthread_create(&th[t], NULL, rt_worker, &jobs[t]) != 0)
			ft_printf("warn: pthread_create falhou no t=%d\n", t);
		t++;
	}
	while (t--)
		pthread_join(th[t], NULL);
	mlx_put_image_to_window(rt->mlx->mlx_ptr, rt->mlx->win_ptr, rt->mlx->img, 0, 0);
}

int render_loop(t_rt *rt)
{
	render_parallel(rt);
	rt->camera->count_samples++;
	if (rt->camera->count_samples < rt->camera->sample_per_pixel)
	{
		ft_printf("Rendering... %d samples per pixel.\n",
			rt->camera->count_samples);
	}
		return 0;
}

void	render_rt(t_rt *rt)
{
	t_mlx	*mlx;

	mlx = rt->mlx;
	ft_printf("Rendering image (multithread)...\n");
	//render_parallel(rt);
	ft_printf("Done.\n");
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	mlx_loop_hook(mlx->mlx_ptr, render_loop, rt);
	mlx_key_hook(mlx->win_ptr, destroy_in_esc, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, destroy, mlx);
	mlx_loop(mlx->mlx_ptr);
}
