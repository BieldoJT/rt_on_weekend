/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:50:38 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/17 14:35:39 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void create_world(t_rt *rt);

void	init_rt(t_rt *rt)
{
	// Inicializa as variáveis do rt
	double aspect_ratio;

	aspect_ratio = 16.0/9.0; // Exemplo de proporção 16:9
	rt->mlx = NULL;
	rt->world_size = 0;
	rt->t_range = (t_interval){0, 0};
	rt->intensity = (t_interval){0, 0};

	// Inicializa o intervalo t_range
	interval_init(&rt->t_range, 0.001, INFINITY);
	// Inicializa o intervalo de intensidade
	interval_init(&rt->intensity, 0.000, 0.999);

	// Define a largura e altura da imagem
	rt->image_width = 800; // Largura da imagem
	rt->image_height = (int)(rt->image_width / aspect_ratio);

	// Inicializa o mlx
	rt->mlx = malloc(sizeof(t_mlx));

	if(rt->image_height < 1)
		rt->image_height = 1;

	// inicializa o mlx
	init_mlx(rt);
	//inicializar a camera
	rt->camera = init_camera(aspect_ratio, rt->image_width, rt->image_height);
	rt->camera->sample_per_pixel = 50; // Inicializa com n amostras por pixel
	rt->camera->pixel_sample_scale = 1.0 / rt->camera->sample_per_pixel;
	rt->camera->max_depth = 50;
	create_world(rt);
}

static void create_world(t_rt *rt)
{
	// Cria o mundo com as esferas e materiais
	// Aloca memória para o array de objetos
	rt->world = malloc(sizeof(t_hittable *) * 4);
	if (!rt->world)
		return ;
	rt->world[rt->world_size++] = sphere_create(vec3(0.0, -100.5, -1.0), 100.0 , lambertian_create(vec3( 0.8,  0.8,  0.0)));
	rt->world[rt->world_size++] = sphere_create(vec3(0.0, 0.0, -1.2), 0.5, metal_create(vec3(0., 0.2, 0.5),0.5)); // meio
	rt->world[rt->world_size++] = sphere_create(vec3(-1.0, 0.0, -1.0), 0.5, dielectric_create(1.0 / 1.5));
	//world[world_size++] = sphere_create(vec3(-1.0, 0.0, -1.0), 0.5, dielectric_create(1.0 / 1.5)); // vidro
	rt->world[rt->world_size++] = sphere_create(vec3(0.0, 2.0, 2.0), 0.5, diffuse_light_create(vec3(50, 50, 50))); //4 4 4

}
