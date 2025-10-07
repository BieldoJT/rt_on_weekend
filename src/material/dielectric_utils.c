/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bieldojt <bieldojt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:18:30 by natrodri          #+#    #+#             */
/*   Updated: 2025/09/17 10:24:58 by bieldojt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../ray.h"

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_mul(n, 2.0 * vec3_dot(v, n))));
}

t_vec3	refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double	cos_th;
	t_vec3	r_out_perp;
	t_vec3	r_out_parl;
	double	k;

	cos_th = fmin(vec3_dot(vec3_mul(uv, -1.0), n), 1.0);
	r_out_perp = vec3_mul(vec3_add(uv, vec3_mul(n, cos_th)), etai_over_etat);
	k = 1.0 - vec3_dot(r_out_perp, r_out_perp);
	r_out_parl = vec3_mul(n, -sqrt(fabs(k)));
	return (vec3_add(r_out_perp, r_out_parl));
}

double	reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * pow(1.0 - cosine, 5.0));
}
