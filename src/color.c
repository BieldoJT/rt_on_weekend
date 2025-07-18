/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:13:40 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/18 16:57:59 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


t_vec3	ray_color(t_ray r, t_rt *rt, int depth)
{
	t_hit_record	rec;
	t_vec3			atten; // Atenuação inicial é branca
	t_ray			sctred;
	t_vec3			emitted_color;
	t_vec3			sctred_color;
	t_scatter_params	params;

	params.r_in = &r;
	params.rec = &rec;
	params.attenuation = &atten;
	params.scattered = &sctred;
	if (depth <= 0)
		return (vec3(0, 0, 0));  // retorna preto se a profundidade máxima for atingida
	if (!hit_world(r, &rec, rt))
		return (vec3(0, 0, 0)); // Cor de fundo se não houver interseção
	emitted_color = rec.material->color_emited;
	if (!rec.material->scatter(rec.material, &params))
		return (emitted_color);
	sctred_color = ray_color(sctred, rt, depth - 1);
	return (vec3_add(emitted_color, vec3_mult_vecs(atten, sctred_color))); // Retorna a cor emitida mais a cor espalhada
}
