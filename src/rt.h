/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:17:55 by gda-conc          #+#    #+#             */
/*   Updated: 2025/09/24 15:57:35 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** =============================================================================
** INCLUDES
** =============================================================================
*/

# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"
# include "vec3/vec3.h"
# include "ray.h"
# include "interval/interval.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

/*
** =============================================================================
** MACROS
** =============================================================================
*/

# define ESC 65307
# define TRUE 1
# define FALSE 0
# define PI 3.1415926535897932385

/*
** =============================================================================
** FORWARD DECLARATIONS & ENUMS
** =============================================================================
*/

typedef struct s_hit_record		t_hit_record;
typedef struct s_material		t_material;
typedef struct s_scatter_params	t_scatter_params;
typedef int						(*t_scatter_fn)(const struct s_material *mat, \
									t_scatter_params *params);
typedef enum e_hittable_type
{
	SPHERE
}								t_hittable_type;

/*
** =============================================================================
** STRUCTURES DEFINITIONS
** =============================================================================
*/

//------------------------------------------------------------------------------
//|                                  MATERIAL                                  |
//------------------------------------------------------------------------------

typedef struct s_scatter_params
{
	const t_ray					*r_in;
	const t_hit_record			*rec;
	t_vec3						*attenuation;
	t_ray						*scattered;
	int							is_specular; //pro metal e o dialectrico
}								t_scatter_params;

typedef struct s_material
{
	t_scatter_fn				scatter;
	t_vec3						albedo;
	double						fuzz;
	double						refractive_index;
	t_vec3						color_emited;
}								t_material;

//------------------------------------------------------------------------------
//|                                 LIGHT                                      |
//------------------------------------------------------------------------------

typedef struct s_point_light
{
	t_vec3	position;
	t_vec3	intensity;
	struct s_point_light	*next;
}	t_point_light;

//------------------------------------------------------------------------------
//|                            HITTABLES (OBJETOS)                             |
//------------------------------------------------------------------------------

typedef struct s_hit_record
{
	double		t;
	t_vec3		p;
	t_vec3		normal;
	t_material	*material;
	int			front_face;
	double		u;
	double		v;
}	t_hit_record;

typedef struct s_hittable
{
	void		*obj;
	int			(*hit)(void *object, t_ray r, t_interval, t_hit_record *rec);
}	t_hittable;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	*material;
}	t_sphere;

typedef struct s_equation
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	disc;
}	t_equation;

typedef struct s_ambient
{
	double	ratio;   /* 0..1 */
	t_vec3	color;   /* 0..1 */
}	t_ambient;


//------------------------------------------------------------------------------
//|                                   CÂMERA                                   |
//------------------------------------------------------------------------------

typedef struct s_camera
{
	t_vec3						camera_center;
	double						focal_length;
	double						viewport_height;
	double						viewport_width;
	t_vec3						viewport_u;
	t_vec3						viewport_v;
	t_vec3						upper_left_corner;
	double						pixel_du_x;
	double						pixel_dv_y;
	int							count_samples;
	int							sample_per_pixel;
	double						pixel_sample_scale;
	int							max_depth;
	t_vec3						background_color;
}								t_camera;




//------------------------------------------------------------------------------
//|                           RENDER & JANELA                        |
//------------------------------------------------------------------------------


typedef struct s_mlx
{
	void						*mlx_ptr;
	void						*win_ptr;
	void						*img;
	char						*addr;
	int							bits_per_pixel;
	int							line_length;
	int							endian;
}								t_mlx;


typedef struct s_rt
{
	t_mlx						*mlx;
	t_camera					*camera;
	int							image_width;
	int							image_height;
	int							world_size;
	t_hittable					**world;
	t_interval					t_range;
	t_interval					intensity;
	t_point_light				*lights;
	t_ambient					ambient;
}								t_rt;

void    set_ambient(t_rt *rt, double ratio, t_vec3 color);

/*
** =============================================================================
** FUNCTION PROTOTYPES
** =============================================================================
*/

//------------------------------------------------------------------------------
//|                                  main.c                                    |
//------------------------------------------------------------------------------
void							init_rt(t_rt *rt);




//------------------------------------------------------------------------------
//|                                 render.c                                   |
//------------------------------------------------------------------------------

void	render_rt(t_rt *rt);
t_vec3							ray_color(t_ray r, t_rt *rt, int depth);

//------------------------------------------------------------------------------
//|                                  mlx.c                                     |
//------------------------------------------------------------------------------
void							init_mlx(t_rt *rt);
void							my_mlx_pixel_put(t_mlx *mlx, int x, int y, \
									int color);
int								destroy(t_mlx *mlx);
int								destroy_in_esc(int keycode, t_mlx *mlx);

//------------------------------------------------------------------------------
//|                                 camera.c                                   |
//------------------------------------------------------------------------------
t_camera						*init_camera(double aspect_ratio, \
									int image_width, int image_height);
void							destroy_camera(t_camera *camera);
t_vec3							get_pixel_center(t_camera *camera, int i, int j,
									t_vec3 pixel00);
t_ray							get_ray(const t_camera *cam, int i, int j,
									int *sample_index);
t_vec3							get_pixel00(t_camera *camera);

//------------------------------------------------------------------------------
//|                                hittable.c                                  |
//------------------------------------------------------------------------------
int								hit_world(t_ray r, t_hit_record *rec, t_rt *rt);
void							set_face_normal(t_hit_record *rec, t_ray r, \
									t_vec3 outward_normal);

//------------------------------------------------------------------------------
//|                                 color.c                                    |
//------------------------------------------------------------------------------

typedef struct s_trace_data
{
	t_hit_record			hit;
	t_scatter_params		scatter_params;
	t_vec3					atten;
	t_ray					ray_next;
	t_vec3					emission;
}	t_trace_data;

int	rr_terminate(t_vec3 *atten);
int	hit_anything(t_rt *rt, t_ray r, double tmax);
int	shadow_blocked(t_rt *rt, t_vec3 p, t_vec3 to_l, double dist_l);
t_vec3	ambient_term(t_rt *rt, const t_hit_record *rec);



//------------------------------------------------------------------------------
//|                                 lights.c                                    |
//------------------------------------------------------------------------------

t_point_light	*point_light_create(t_vec3 position, double intensity, t_vec3 color);
void	point_light_add(t_point_light **lights, t_point_light *new_light);
void	point_light_destroy(t_point_light **light);
t_vec3	point_light_diffuse(t_rt *rt, const t_hit_record *rec, t_point_light *light);

//------------------------------------------------------------------------------
//|                                 sphere.c                                   |
//------------------------------------------------------------------------------
t_hittable						*sphere_create(t_vec3 center, double radius, \
									t_material *material);
void							sphere_destroy(t_hittable *hittable);
int								sphere_hit(void *object, t_ray r, t_interval t,
									t_hit_record *rec);
double							hit_sphere(t_vec3 center, double radius, \
									t_ray r);

/*
** Densidade do PDF (pelo sólido ângulo) de lançar uma direção 'dir'
** da origem 'origin' que acerta a esfera 'sp'. Retorna 0.0 se não visível.
** sp deve ser (t_sphere*), mas a assinatura fica genérica (void*) para pdf.h.
*/
double	sphere_pdf_value_from(void *sp, t_vec3 origin, t_vec3 dir);
/*
** Gera uma direção aleatória (no MUNDO) que aponta para a esfera 'sp'
** vista da origem 'origin', restrita ao cone que cobre a esfera.
*/
t_vec3	sphere_random_dir_to(void *sp, t_vec3 origin);

//------------------------------------------------------------------------------
//|                                material.c                                  |
//------------------------------------------------------------------------------

//---------------------------------LAMBERTIAN---------------------------------//
t_material						*lambertian_create(t_vec3 albedo);
double	lambertian_scattering_pdf(const t_material *mat, const t_ray *r_in,
			const t_hit_record *rec, t_vec3 *scattered);
t_vec3	lambertian_emitted(const t_material *mat, const t_hit_record *rec, double u, double v, t_vec3 p);
void	material_set_lambertian(t_material *mat, t_vec3 albedo);

//------------------------------------METAL------------------------------------//
t_material						*metal_create(t_vec3 albedo, double fuzz);
//double	metal_scattering_pdf(const t_material *mat, const t_ray *r_in, const t_hit_record *rec, const t_ray *scattered);
//t_vec3	metal_emitted(const t_material *mat, const t_hit_record *rec, double u, double v, t_vec3 p);
void	material_set_metal(t_material *mat, t_vec3 albedo, double fuzz);

//---------------------------------DIELECTRIC---------------------------------//
t_material						*dielectric_create(double refractive_index);
//double	dielectric_scattering_pdf(const t_material *mat, const t_ray *r_in, const t_hit_record *rec, const t_ray *scattered);
//t_vec3	dielectric_emitted(const t_material *mat, const t_hit_record *rec, double u, double v, t_vec3 p);
void	material_set_dielectric(t_material *mat, double refractive_index);

//--------------------------------DIFFUSE LIGHT-------------------------------//
t_material						*diffuse_light_create(t_vec3 albedo);
//double	diffuse_light_scattering_pdf(const t_material *mat, const t_ray *r_in, const t_hit_record *rec, const t_ray *scattered);
//t_vec3	diffuse_light_emitted(const t_material *mat, const t_hit_record *rec, double u, double v, t_vec3 p);
//void	material_set_diffuse_light(t_material *mat, t_vec3 emit_color);

void							material_destroy(t_material *m);


//------------------------------------------------------------------------------
//|                                 utils.c                                    |
//------------------------------------------------------------------------------
double							degree_to_radian(double degree);
double							random_double(void);
double							random_double_range(double min, double max);
int								rgb_to_int(int r, int g, int b);
t_vec3							sample_square(void);

#endif
