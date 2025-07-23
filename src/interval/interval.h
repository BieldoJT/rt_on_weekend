/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:12:07 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/22 22:11:15 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include <math.h>

typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

/* inicializa intervalo vazio */
void	interval_init_empty(t_interval *i);
/* inicializa com limites */
void	interval_init(t_interval *i, double min, double max);
/* tamanho (max - min) */
double	interval_size(const t_interval *i);
/* testa se x está em [min, max] */
int		interval_contains(const t_interval *i, double x);
/* testa se x está em (min, max) */
int		interval_surrounds(const t_interval *i, double x);
double	interval_clamp(const t_interval *i, double x);
void expand_interval(t_interval *interval ,double delta);

extern const t_interval	g_interval_empty;
extern const t_interval	g_interval_universe;

#endif
