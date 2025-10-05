/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/10/03 16:44:05 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

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

void	int_to_img(t_rt *rt)
{
	int	j;
	int	i;

	j = 0;
	while (j < rt->image_height)
	{
		i = 0;
		while (i < rt->image_width)
		{
			my_mlx_pixel_put(rt->mlx, i, j, rt->image_index[j][i]);
			i++;
		}
		j++;
	}
}
