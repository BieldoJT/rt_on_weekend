/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:59:32 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/16 17:42:33 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"








int main()
{
	t_rt *rt;

	rt = malloc(sizeof(t_rt));
	if (!rt)
		return (1);

	init_rt(rt);
	render_rt(rt);


	return (0);
}
