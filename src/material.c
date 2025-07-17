#include "rt.h"
#include "ray.h"        /* t_ray, ray() *//* t_hit_record, hit_world() */
#include "vec3.h"      /* vec3_reflect(), vec3_dot(), vec3_unit_vector() */
#include <stdlib.h>
#include <math.h>

/* ================= Lam­ber­ti­an ================= */

static int lambertian_scatter(const t_material *self,
                              const t_ray *r_in,
                              const t_hit_record *rec,
                              t_vec3 *attenuation,
                              t_ray *scattered)
{
    (void)r_in;
    t_vec3 dir = vec3_add(rec->normal, random_unit_vector());
    if (vec3_near_zero(dir))
        dir = rec->normal;
    *scattered  = ray(rec->p, dir);
    *attenuation = self->albedo;
    return 1;
}

t_material *lambertian_create(t_vec3 albedo)
{
    t_material *m = malloc(sizeof(*m));
    if (!m) return NULL;
    m->scatter = lambertian_scatter;
    m->albedo  = albedo;
    m->fuzz    = 0.0;
    m->refractive_index = 1.0; // Valor padrão, não usado
    m->color_emited = vec3(0.0, 0.0, 0.0); // Cor emitida padrão
    return m;
}

/* =================== Metal =================== */

static int metal_scatter(const t_material *self,
                         const t_ray *r_in,
                         const t_hit_record *rec,
                         t_vec3 *attenuation,
                         t_ray *scattered)
{
    t_vec3 reflected   = vec3_reflect(r_in->dir, rec->normal);
    reflected = vec3_add(vec3_unit_vector(reflected),vec3_mul(random_unit_vector(),self->fuzz));

    *scattered   = ray(rec->p, reflected);
    *attenuation = self->albedo;

    /* só aceita se for para fora */
    return (vec3_dot(scattered->dir, rec->normal) > 0.0);
    //return 1;
}

t_material *metal_create(t_vec3 albedo, double fuzz)
{
    t_material *m = malloc(sizeof(*m));
    if (!m) return NULL;
    m->scatter = metal_scatter;
    m->albedo  = albedo;
    /* garante 0 ≤ fuzz ≤ 1 */
    m->fuzz  = (fuzz < 1.0) ? fuzz : 1.0;
    m->refractive_index = 1.0; // Valor padrão, não usado
    m->color_emited = vec3(0.0, 0.0, 0.0); // Cor emitida padrão
    return m;
}

/* ================ dielectric ================= */

static double reflectance(double cos, double refr_index)
{
    /* fórmula de Fresnel */
    double r0 = (1 - refr_index) / (1 + refr_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cos), 5);
}


static int dielectric_scatter(const t_material *self,
                              const t_ray *r_in,
                              const t_hit_record *rec,
                              t_vec3 *attenuation,
                              t_ray *scattered)
{
    (void)self; // Ignora self, pois não é usado neste material
    *attenuation = self->albedo; // Define a atenuação como a cor do material
    double ri;
    if (rec->front_face)
        ri = 1.0 / self->refractive_index; // Refractive index for front face
    else
        ri = self->refractive_index; // Refractive index for back face
    t_vec3 unit_direction = vec3_unit_vector(r_in->dir);
    double cos_theta = fmin(vec3_dot(vec3_neg(unit_direction), rec->normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    int cannot_refract = ri * sin_theta > 1.0;
    t_vec3 direction;
    if(cannot_refract || reflectance(cos_theta, ri) > random_double())
        direction = vec3_reflect(unit_direction, rec->normal);
    else
        direction = vec3_refract(unit_direction, rec->normal, ri);

    *scattered = ray(rec->p, direction);
    return 1; // Sempre retorna 1, pois o espalhamento é garantido

}


t_material *dielectric_create(double refractive_index)
{
    t_material *m = malloc(sizeof(*m));
    if (!m) return NULL;
    m->scatter = dielectric_scatter;
    m->albedo  = vec3(1.0, 1.0, 1.0); // Albedo para materiais dielétricos é geralmente branco
    m->fuzz = 0.0;
    m->refractive_index = refractive_index; // Define o índice de refração
    m->color_emited = vec3(0.0, 0.0, 0.0); // Cor emitida padrão
    return m;
}


/* ================ difuse ligth ================= */

static int diffuse_ligth_scatter(const t_material *self,
                              const t_ray *r_in,
                              const t_hit_record *rec,
                              t_vec3 *attenuation,
                              t_ray *scattered)
{
    (void)r_in; // Ignora r_in, pois não é usado neste material
    (void)rec;  // Ignora rec, pois não é usado neste material
    *attenuation = self->albedo; // Define a atenuação como a cor do material
    *scattered = ray(rec->p, random_unit_vector()); // Espalha em uma direção aleatória
    return 0; // Retorna 0, pois não há espalhamento real, é uma fonte de luz
}

t_material *diffuse_light_create(t_vec3 albedo)
{
    t_material *m = malloc(sizeof(*m));
    if (!m) return NULL;
    m->scatter = diffuse_ligth_scatter; // Não tem método de espalhamento, pois é uma fonte de luz
    m->albedo  = albedo;
    m->fuzz    = 0.0;
    m->refractive_index = 1.0; // Valor padrão, não usado
    m->color_emited = albedo; // A cor emitida é a mesma que o albedo
    return m;
}


/* ================ Destrutor ================= */

void material_destroy(t_material *m)
{
    free(m);
}
