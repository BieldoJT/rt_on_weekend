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

t_interval	interval_empty(void)
{
	t_interval	i;

	i.min = INFINITY;
	i.max = -INFINITY;
	return (i);
}

t_interval	interval_universe(void)
{
	t_interval	i;

	i.min = -INFINITY;
	i.max = INFINITY;
	return (i);
}

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