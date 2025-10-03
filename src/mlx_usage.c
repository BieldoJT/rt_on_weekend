/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:04:00 by gda-conc          #+#    #+#             */
/*   Updated: 2025/10/03 18:01:42 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_mlx(t_rt *rt)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return ;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			rt->image_width, rt->image_height, "MiniRT");
	mlx->img = mlx_new_image(mlx->mlx_ptr, rt->image_width,
			rt->image_height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	rt->mlx = mlx;
}
int	destroy(t_rt *rt)
{
	t_mlx	*mlx;

	mlx = rt->mlx;
	free(rt->camera);
	free_world(rt);
	free_create_lights(rt);
	free_index(rt);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	all_free(mlx->scene);
	free(mlx->mlx_ptr);
	free(rt->mlx);
	free(rt);
	exit(0);
	return (0);
}

int	destroy_in_esc(int keycode, t_rt *rt)
{
	if (keycode == ESC)
		destroy(rt);
	return (0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
