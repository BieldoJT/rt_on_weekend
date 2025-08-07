#include "vec3.h"

t_vec3  vec3_normalize(t_vec3 v)
{
    double  len;

    len = vec3_length(v);
    if (len == 0)
        return (vec3(0, 0, 0));
    return (vec3(v.x / len, v.y / len, v.z / len));
}