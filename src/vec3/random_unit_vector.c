/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_unit_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:06:27 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/17 18:07:03 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	random_unit_vector(void)
{
	t_vec3	v;
	double	lensq;

	while (1)
	{
		v = random_vec3_in_range(-1.0, 1.0);
		lensq = vec3_length_squared(v);
		if (1e-160 < lensq && lensq <= 1.0)
			return (vec3_div(v, sqrt(lensq)));
	}
}
