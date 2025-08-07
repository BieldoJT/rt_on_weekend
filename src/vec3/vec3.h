/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:52:41 by natrodri          #+#    #+#             */
/*   Updated: 2025/07/18 15:52:43 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H
# include <math.h>
# include <stdlib.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

t_vec3	vec3(double x, double y, double z);

// Operações básicas
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_neg(t_vec3 v);
t_vec3	vec3_mul(t_vec3 v, double t);
t_vec3	vec3_div(t_vec3 v, double t);

// Operações in-place (modificam o vetor apontado)
t_vec3	vec3_mult_vecs(t_vec3 a, t_vec3 b);

// Operações in-place (modificam o vetor apontado)
void	vec3_add_inplace(t_vec3 *a, t_vec3 b);
void	vec3_mul_inplace(t_vec3 *v, double t);
void	vec3_div_inplace(t_vec3 *v, double t);

// Produto escalar e vetorial
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

// Comprimento e normalização
double	vec3_length(t_vec3 v);
double	vec3_length_squared(t_vec3 v);
t_vec3	vec3_unit_vector(t_vec3 v);
t_vec3	random_vec3(void);
t_vec3	random_vec3_in_range(double min, double max);
t_vec3	random_unit_vector(void);
t_vec3	random_on_hemisphere(t_vec3 normal);
int		vec3_near_zero(t_vec3 v);
t_vec3	vec3_reflect(t_vec3 v, t_vec3 n);
t_vec3	vec3_refract(t_vec3 uv, t_vec3 n, double ref_index);
double	random_double(void);
double	random_double_range(double min, double max);
t_vec3  vec3_normalize(t_vec3 v);

#endif