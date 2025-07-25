/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:17:55 by gda-conc          #+#    #+#             */
/*   Updated: 2025/07/25 16:16:49 by natrodri         ###   ########.fr       */
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

typedef	struct s_plane
{
	t_vec3	point;
	t_vec3	norma;
	t_material	*material;
}	t_plane;

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
}								t_rt;

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
void							render_rt(t_rt *rt);
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
t_ray							get_ray(const t_camera *cam, int i, int j);
t_vec3							get_pixel00(t_camera *camera);

//------------------------------------------------------------------------------
//|                                hittable.c                                  |
//------------------------------------------------------------------------------
int								hit_world(t_ray r, t_hit_record *rec, t_rt *rt);
void							set_face_normal(t_hit_record *rec, t_ray r, \
									t_vec3 outward_normal);

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

//------------------------------------------------------------------------------
//|                                material.c                                  |
//------------------------------------------------------------------------------
t_material						*lambertian_create(t_vec3 albedo);
t_material						*metal_create(t_vec3 albedo, double fuzz);
t_material						*dielectric_create(double refractive_index);
t_material						*diffuse_light_create(t_vec3 albedo);
void							material_destroy(t_material *m);

//------------------------------------------------------------------------------
//|                                 utils.c                                    |
//------------------------------------------------------------------------------
double							degree_to_radian(double degree);
double							random_double(void);
double							random_double_range(double min, double max);
int								rgb_to_int(int r, int g, int b);
t_vec3							sample_square(void);





t_hittable	*plane_creat(t_vec3 point, t_vec3 normal, t_material *material);


#endif
