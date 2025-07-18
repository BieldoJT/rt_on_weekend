/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:00:20 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 18:07:10 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interval.h"

/* vazio: min = +inf, max = -inf */
const t_interval	g_interval_empty = {INFINITY, -INFINITY};
/* universo: min = -inf, max = +inf */
const t_interval	g_interval_universe = {-INFINITY, INFINITY};

void	interval_init_empty(t_interval *i)
{
	i->min = INFINITY;
	i->max = -INFINITY;
}

void	interval_init(t_interval *i, double min, double max)
{
	i->min = min;
	i->max = max;
}

double	interval_size(const t_interval *i)
{
	return (i->max - i->min);
}
