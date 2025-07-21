/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:08:40 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/17 18:09:20 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	random_vec3(void)
{
	return (vec3(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand()
			/ (double)RAND_MAX));
}
