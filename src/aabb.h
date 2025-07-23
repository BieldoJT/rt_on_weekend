#ifndef AABB_H
# define AABB_H

# include "vec3/vec3.h"
# include "interval/interval.h"
# include "ray.h"

//init aabb
//void	aabb_init(t_interval *x, t_interval *y, t_interval *z);

typedef struct s_aabb
{
	t_interval	x;
	t_interval	y;
	t_interval	z;
}	t_aabb;

typedef struct s_dist_point
{
	double	inv_d;
	double	t0;
	double	t1;
	double orig[3];
	double dir[3];
} t_dist_point;

t_aabb	aabb(t_interval x, t_interval y, t_interval z);
t_aabb	*aabb_empty(void);
void	get_point(t_aabb *box ,t_vec3 a, t_vec3 b);
int	hit_aabb(const t_aabb *b, const t_ray *r, t_interval *ray_t);



#endif
