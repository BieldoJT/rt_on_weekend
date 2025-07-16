#include "rt.h"


double degree_to_radian(double degree)
{
	double pi = 3.1415926535897932385;
	return degree * (pi / 180.0);
}

int rgb_to_int(int r, int g, int b) {
	return (r << 16) | (g << 8) | b;
}



double linear_to_gamma(double x)
{
	if(x > 0)
		return sqrt(x);
	return 0.0; // retorna 0 para valores negativos ou zero
}





int main()
{
	t_mlx *mlx;
	t_camera *camera;
	int image_width;
	int image_height;
	int i;
	int j;
	t_ray r;
	t_vec3 pixel_color;
	double aspect_ratio;
	int packed_color;
	t_hittable *world[4];
	int world_size = 0;
	t_interval t_range;
	t_interval intensity;
	srand(time(NULL));

	// Inicializa o intervalo t_range
	interval_init(&t_range, 0.001, INFINITY);
	// Inicializa o intervalo de intensidade
	interval_init(&intensity, 0.000, 0.999);

	world[world_size++] = sphere_create(vec3(0.0, -100.5, -1.0), 100.0 , lambertian_create(vec3( 0.8,  0.8,  0.0)));
	world[world_size++] = sphere_create(vec3(0.0, 0.0, -1.2), 0.5, metal_create(vec3(0., 0.2, 0.5), 0.03)); // meio
	world[world_size++] = sphere_create(vec3(-1.0, 0.0, -1.0), 0.5, diffuse_light_create(vec3(0, 0, 255)));
	//world[world_size++] = sphere_create(vec3(-1.0, 0.0, -1.0), 0.5, dielectric_create(1.0 / 1.5)); // vidro
	world[world_size++] = sphere_create(vec3(1.0, 0.0, -1.0), 0.5, diffuse_light_create(vec3(0.8, 0.8, 0.8)));


	mlx = malloc(sizeof(t_mlx));


	// Define a proporção da imagem
	aspect_ratio = 16.0/9.0; // Exemplo de proporção 16:9
	image_width = 800; // Largura da imagem
	image_height = (int)(image_width / aspect_ratio);
	if(image_height < 1)
		image_height = 1;

	// inicializa o mlx
	init_mlx(mlx, image_width, image_height);

	//inicializar a camera
	camera = init_camera(aspect_ratio, image_width, image_height);


	//loop para criar a imagem
	j = 0;
	while(j < image_height)
	 {
		ft_printf( "\rScanlines remaining: %d ", image_height - j);
		i = 0;
		while (i < image_width)
		{
			// posição do centro do pixel (i,j)
			pixel_color = vec3(0, 0, 0);

			int s = 0;
			while(s < camera->sample_per_pixel)
			{
				r = get_ray(camera, i, j);
				pixel_color = vec3_add(pixel_color, ray_color(r, world, world_size, t_range, camera->max_depth));

				s++;
			}
			//cria o raio da camera até o pixel
			//media
			pixel_color = vec3_mul(pixel_color, camera->pixel_sample_scale);

			pixel_color.x = linear_to_gamma(pixel_color.x);
			pixel_color.y = linear_to_gamma(pixel_color.y);
			pixel_color.z = linear_to_gamma(pixel_color.z);
			/* aplica clamp e converte para byte */
			int ir = (int)(256 * interval_clamp(&intensity, pixel_color.x));
			int ig = (int)(256 * interval_clamp(&intensity, pixel_color.y));
			int ib = (int)(256 * interval_clamp(&intensity, pixel_color.z));

			/* empacota e desenha o pixel */
			packed_color = rgb_to_int(ir, ig, ib);

			// Define pixel (considera endian = 0 / little endian)
			my_mlx_pixel_put(mlx, i, j, packed_color);
			i++;
		}
		j++;
	}
	ft_printf("\nDone.\n");

	// Mostra imagem na janela
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);

	mlx_key_hook(mlx->win_ptr, destroy_in_esc, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, destroy, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
