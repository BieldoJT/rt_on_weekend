/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_double_range.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:56:05 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/17 17:56:08 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}
