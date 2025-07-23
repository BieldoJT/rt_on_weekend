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

t_aabb	aabb(t_interval x, t_interval y, t_interval z);
t_aabb	aabb_empty(void);



#endif
