#include "aabb.h"

t_aabb	*init_aabb(t_interval x, t_interval y, t_interval z)
{
	t_aabb	*result;

	result = malloc(sizeof(t_aabb));
	if (!result)
		return (NULL);
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}

t_aabb *aabb_empty(void)
{
	t_aabb	*result;

	result = malloc(sizeof(t_aabb));
	if (!result)
		return (NULL);
	result->x = g_interval_empty;
	result->y = g_interval_empty;
	result->z = g_interval_empty;
	return (result);
}

void get_point(t_aabb *box ,t_vec3 a, t_vec3 b)
{
	if (a.x <= b.x)
		interval_init(&box->x, a.x, b.x);
	else
		interval_init(&box->x, b.x, a.x);
	if (a.y <= b.y)
		interval_init(&box->y, a.y, b.y);
	else
		interval_init(&box->y, b.y, a.y);
	if (a.z <= b.z)
		interval_init(&box->z, a.z, b.z);
	else
		interval_init(&box->z, b.z, a.z);
}


t_interval axis_interval(t_aabb box, int n)
{
	if (n == 1)
		return box.y;
	else if (n == 2)
		return box.z;
	else
		return box.x;
}



int hit_aabb(const t_aabb *b, const t_ray *r, t_interval *ray_t)
{
	int	axis;
	double	inv_d, t0, t1;
	const double orig[3] = { r->orig.x, r->orig.y, r->orig.z };
	const double dir [3] = { r->dir.x,  r->dir.y,  r->dir.z };
	double tmp;

	for (axis = 0; axis < 3; ++axis)
	{
		const t_interval *iv = (axis == 0 ? &b->x
								 : axis == 1 ? &b->y
								             : &b->z);
		inv_d = 1.0 / dir[axis];
		t0    = (iv->min - orig[axis]) * inv_d;
		t1    = (iv->max - orig[axis]) * inv_d;
		if (inv_d < 0.0)
		{
			double tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if (t0 > ray_t->min) ray_t->min = t0;
		if (t1 < ray_t->max) ray_t->max = t1;
		if (ray_t->max <= ray_t->min)
			return (0);
	}
	return (1);
}
