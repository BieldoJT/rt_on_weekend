/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:07:15 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 18:10:51 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interval.h"

int	interval_contains(const t_interval *i, double x)
{
	return (i->min <= x && x <= i->max);
}

int	interval_surrounds(const t_interval *i, double x)
{
	return (i->min < x && x < i->max);
}

double	interval_clamp(const t_interval *i, double x)
{
	if (x < i->min)
		return (i->min);
	if (x > i->max)
		return (i->max);
	return (x);
}
