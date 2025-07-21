/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_near_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:15:34 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/17 18:15:41 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

int	vec3_near_zero(t_vec3 v)
{
	const double	s = 1e-8;

	if (fabs(v.x) < s
		&& fabs(v.y) < s
		&& fabs(v.z) < s)
		return (1);
	return (0);
}
