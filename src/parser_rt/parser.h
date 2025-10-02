#ifndef PARSER_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include "../../lib/libft.h"

typedef struct s_prs_ambient
{
    double intensity;
    int color[3];
} t_prs_ambient;

typedef struct s_prs_camera
{
    double pos[3];
    double orientation[3];
    double fov;
} t_prs_camera;

typedef struct s_prs_light
{
    double pos[3];
    double intensity;
    int color[3];
    struct s_prs_light *next;
} t_prs_light;

typedef struct s_prs_sphere
{
    double pos[3];
    double radius;
    int color[3];
    struct s_prs_sphere *next;
} t_prs_sphere;

typedef struct s_prs_plane
{
    double pos[3];
    double orientation[3];
    int color[3];
    struct s_prs_plane *next;
} t_prs_plane;

typedef struct s_prs_cylinder
{
    double pos[3];
    double orientation[3];
    double radius;
    double height;
    int color[3];
    struct s_prs_cylinder *next;
} t_prs_cylinder;

typedef struct s_scene
{
    t_prs_sphere  *spheres;
    t_prs_plane   *planes;
    t_prs_cylinder *cylinders;
    t_prs_light   *lights;
    t_prs_camera  camera;
    t_prs_ambient ambient;
} t_scene;

double      ft_atof(char *str);
void	free_split(char **tok);
int	convert_vec(char *str, double *vec);
int	convert_color(char *str, int *color);
void parse_light(char *str, t_scene *scene, char *line, int fd);
void parse_camera(char *str, t_scene *scene, char *line, int fd);
void creat_ambient(char *str, t_scene *scene, char *line, int fd);
void parse_sphere(char *str, t_scene *scene, char *line, int fd);
void free_lights(t_prs_light *light);
void parse_plane(char *str, t_scene *scene, char *line, int fd);
void free_spheres(t_prs_sphere *s);
void free_planes(t_prs_plane *p);
void parse_cylinder(char *str, t_scene *scene, char *line, int fd);
void	free_cylinders(t_prs_cylinder *cy);
void	all_free(t_scene *scene);
void parser_rt(char *file, t_scene *scene);
void	bad(char **tok, t_scene *scene, char *line, int fd);

#endif