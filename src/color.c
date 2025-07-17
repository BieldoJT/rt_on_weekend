/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:13:40 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/16 21:49:40 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "color.h"


t_vec3	ray_color(t_ray r,t_rt *rt, int depth)
{
	t_hit_record	rec;
	t_vec3			atten; // Atenuação inicial é branca
	t_ray			sctred;
	t_vec3			emitted_color;
	t_vec3			sctred_color;

	if (depth <= 0)
		return (vec3(0, 0, 0));  // retorna preto se a profundidade máxima for atingida
	if (!hit_world(r, &rec, rt))
		return (vec3(0, 0, 0)); // Cor de fundo se não houver interseção
	emitted_color = rec.material->color_emited;
	if (!rec.material->scatter(rec.material, &r, &rec, &atten, &sctred))
		return (emitted_color); // Retorna a cor emitida se não houver espalhamento
	sctred_color = ray_color(sctred, rt, depth - 1);
	return (vec3_add(emitted_color, vec3_mult_vecs(atten, sctred_color))); // Retorna a cor emitida mais a cor espalhada
}
