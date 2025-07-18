/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:12:07 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 18:13:17 by natrodri         ###   ########.fr       */
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

extern const t_interval	g_interval_empty;
extern const t_interval	g_interval_universe;

#endif
