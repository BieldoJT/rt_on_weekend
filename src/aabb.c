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

t_aabb	*aabb_empty(void)
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

void	get_point(t_aabb *box ,t_vec3 a, t_vec3 b)
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


static t_interval	*axis_interval(t_aabb box, int n)
{
	if (n == 1)
		return &box.y;
	else if (n == 2)
		return &box.z;
	else
		return &box.x;
}


static void	get_ray_values(t_ray *r,t_dist_point *values)
{
	values->orig[0] = r->orig.x;
	values->orig[1] = r->orig.y;
	values->orig[2] = r->orig.z;
	values->dir[0] = r->dir.x;
	values->dir[1] = r->dir.y;
	values->dir[2] = r->dir.z;
}

static void	get_dist_point(int axis, t_dist_point *values, t_aabb *b)
{
	const t_interval *iv;
	iv = axis_interval(*b, axis);

	values->inv_d = 1.0 / values->dir[axis];
	values->t0 = (iv->min - values->orig[axis]) * values->inv_d;
	values->t1 = (iv->max - values->orig[axis]) * values->inv_d;
	if (values->inv_d < 0.0)
	{
		double tmp = values->t0;
		values->t0 = values->t1;
		values->t1 = tmp;
	}
}

int	hit_aabb(const t_aabb *b, const t_ray *r, t_interval *ray_t)
{
	int				axis;
	double			tmp;
	t_dist_point	values;

	get_ray_values(r, &values);
	axis = 0;
	while (axis < 3)
	{
		get_dist_point(b, &values, axis);

		if (values.t0 > ray_t->min)
			ray_t->min = values.t0;
		if (values.t1 < ray_t->max)
			ray_t->max = values.t1;
		if (ray_t->max <= ray_t->min)
			return (0);
		axis++;
	}
	return (1);
}
