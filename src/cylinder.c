#include "rt.h"

static void    encapsulate_var(double *var, t_ray r, t_cylinder *cld)
{
    t_vec3 oc;

    oc = vec3_sub(r.orig, cld->center);
    var[0] = vec3_length_squared(r.dir) - pow(vec3_dot(r.dir, cld->axis), 2);
    var[1] = 2 * (vec3_dot(r.dir, oc) - (vec3_dot(r.dir, cld->axis) * vec3_dot(oc, cld->axis)));
    var[2] = vec3_length_squared(oc) - pow(vec3_dot(oc, cld->axis), 2) - (cld->radius * cld->radius);
}

static int bhaskara(double *abc, double *t0, double *t1)
{
    double discriminant;
    double sqrt_discriminant;

    discriminant = (abc[1] * abc[1]) - (4.0 * abc[0] * abc[2]);
    if (discriminant < 0)
        return (0);
    sqrt_discriminant = sqrt(discriminant);
    *t0 = (-abc[1] - sqrt_discriminant) / (2.0 * abc[0]);
    *t1 = (-abc[1] + sqrt_discriminant) / (2.0 * abc[0]);
    if (*t0 > *t1)
    {
        double temp = *t0;
        *t0 = *t1;
        *t1 = temp;
    }
    return (1);
}

int hit_cylinder(t_cylinder *cld, t_ray r, t_interval t_range, t_hit_record *rec)
{
    double abc[3];
    double t0;
    double t1;
    t_vec3 oc;
    t_vec3 projected;

    encapsulate_var(abc, r, cld);
    if (!bhaskara(abc, &t0, &t1))
        return (0);
    if (t0 > t_range.min && t0 < t_range.max)
    {
        rec->t = t0;
        rec->p = ray_at(r, rec->t);
        rec->material = cld->material;
        oc = vec3_sub(rec->p, cld->center);
        projected = vec3_mul(cld->axis, vec3_dot(oc, cld->axis));
        rec->normal = vec3_normalize(vec3_sub(oc, projected));
        return (1);
    }
    if (t1 > t_range.min && t1 < t_range.max)
    {
        rec->t = t1;
        rec->p = ray_at(r, rec->t);
        rec->material = cld->material;
        oc = vec3_sub(rec->p, cld->center);
        projected = vec3_mul(cld->axis, vec3_dot(oc, cld->axis));
        rec->normal = vec3_normalize(vec3_sub(oc, projected));
        return (1);
    }
    return (0);
}

t_hittable *cylinder_create(t_vec3 center, t_vec3 axis, double radius, t_material *mat)
{
    t_hittable *hittable_obj;
    t_cylinder *cylinder_data;

    hittable_obj = malloc(sizeof(t_hittable));
    cylinder_data = malloc(sizeof(t_cylinder));
    if (!hittable_obj || !cylinder_data)
        return (NULL);
    cylinder_data->center = center;
    cylinder_data->axis = vec3_normalize(axis);
    cylinder_data->radius = radius;
    cylinder_data->height = 0;
    cylinder_data->material = mat;
    hittable_obj->obj = cylinder_data;
    hittable_obj->hit = (int (*)(void *, t_ray, t_interval, t_hit_record *))hit_cylinder;
    return (hittable_obj);
}