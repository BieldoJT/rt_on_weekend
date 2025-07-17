#ifndef RT_H
# define RT_H

# include "../lib/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include "vec3.h"
# include "ray.h"
# include <math.h>
# include "interval.h"
# include <time.h>

# include <float.h>




# define TRUE 1
# define FALSE 0
# define PI 3.1415926535897932385


typedef struct s_hit_record  t_hit_record;

typedef struct s_material   t_material;

typedef int (*t_scatter_fn)(const t_material *self,
                            const t_ray *r_in,
                            const t_hit_record *rec,
                            t_vec3 *attenuation,
                            t_ray *scattered);

/* “Base class” para todos os materiais */
struct s_material
{
    t_scatter_fn  scatter;  /* método virtual */
    t_vec3        albedo;   /* cor difusa ou refletância */
    double        fuzz;     /* para metal; ignorado em Lambertian */
	double		refractive_index; /* índice de refração, usado em materiais como vidro */
    t_vec3      color_emited;    /* cor do material, usada para renderização */
};

typedef struct s_hit_record
{
	double t;          // parâmetro t do raio
	t_vec3 p;         // ponto de interseção
	t_vec3 normal;    // normal na interseção
	double u; // coordenada u da textura
	double v; // coordenada v da textura
	t_material *material; // material do objeto atingido
	int front_face;   // se a face normal está voltada para o raio

} t_hit_record;

typedef struct s_hittable
{
	void *obj; // ponteiro para o objeto (ex: esfera)
	int (*hit)(void *object,
		t_ray r,
		double t_min,
		double t_max,
		t_hit_record *rec);
} t_hittable;


typedef struct s_sphere
{
	t_vec3 center; // centro da esfera
	double radius; // raio da esfera
	t_material *material; // material da esfera (opcional)

} t_sphere;




typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_camera
{
	t_vec3 camera_center;
	double focal_length;
	double viewport_height;
	double viewport_width;
	t_vec3 viewport_u;
	t_vec3 viewport_v;
	double pixel_du_x;
	double pixel_dv_y;
	t_vec3 upper_left_corner;
	int sample_per_pixel;
	double pixel_sample_scale; // escala de amostragem por pixel
	int max_depth; // profundidade máxima de recursão
	t_vec3 background_color; // cor de fundo da cena
}	t_camera;

typedef struct s_rt
{
	t_mlx *mlx;
	t_camera *camera;
	int image_width;
	int image_height;
	int world_size;
	t_hittable **world; // array de objetos
	t_interval t_range; // intervalo de t para o ray tracing
	t_interval intensity; // intervalo de intensidade para clamping
}	t_rt;



typedef enum e_hittable_type
{
	SPHERE // Esfera
	// + outras futuras primitivas
}	t_hittable_type;


// Funções de inicialização
void	init_rt(t_rt *rt);
void	render_rt(t_rt *rt);
//mlx
void	init_mlx(t_rt *rt);
int		destroy(t_mlx *mlx);
int	destroy_in_esc(int keycode, t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		rgb_to_int(int r, int g, int b);

//camera
t_camera *init_camera(double aspect_ratio, int image_width, int image_height);
t_vec3 get_pixel00(t_camera *camera);
void destroy_camera(t_camera *camera);
t_vec3 get_pixel_center(t_camera *camera, int i, int j, t_vec3 pixel00);
t_ray   get_ray(const t_camera *cam, int i, int j);
t_vec3  sample_square(void);

double	hit_sphere(t_vec3 center, double radius, t_ray r);

double degree_to_radian(double degree);
double  random_double(void);
double  random_double_range(double min, double max);

int	hit_world(t_ray r, t_hit_record *rec, t_rt *rt);

void	render_rt(t_rt *rt);

//color.c
t_vec3	ray_color(t_ray r,t_rt *rt, int depth);
// hittable.c
int		hit_world(t_ray r, t_hit_record *rec, t_rt *rt);
void	set_face_normal(t_hit_record *rec, t_ray r, t_vec3 outward_normal);

t_material *lambertian_create(t_vec3 albedo);
t_material *metal_create(t_vec3 albedo, double fuzz);
t_material *dielectric_create(double refractive_index);
t_material *diffuse_light_create(t_vec3 albedo);

/* Destrutor único */
void        material_destroy(t_material *m);


t_hittable *sphere_create(t_vec3 center, double radius, t_material *material);
void sphere_destroy(t_hittable *hittable);
int sphere_hit(void *object, t_ray r, double t_min, double t_max, t_hit_record *rec);


#endif
