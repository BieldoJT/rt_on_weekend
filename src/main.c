/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:59:32 by gda-conc          #+#    #+#             */
/*   Updated: 2025/10/07 11:37:04 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(int ac, char **av)
{
	t_rt	*rt;
	t_scene	scene;

	if (ac != 2)
		return (printf("number arguments invalid"), 1);
	parser_rt(av[1], &scene);
	rt = malloc(sizeof(t_rt));
	if (!rt)
		return (1);
	init_rt(rt, &scene);
	render_rt(rt, &scene);
	return (0);
}
