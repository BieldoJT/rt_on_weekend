/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_vec3_in_range.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:07:23 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/17 18:08:16 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	random_vec3_in_range(double min, double max)
{
	return (vec3(min + (rand() / (double)RAND_MAX) * (max - min),
			min + (rand() / (double)RAND_MAX) * (max - min),
			min + (rand() / (double)RAND_MAX) * (max - min)
		));
}
