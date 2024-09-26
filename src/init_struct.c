/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:19:44 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/26 22:07:52 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// function to generate ray
// x and y are the coordinates on the image plane
t_ray	make_ray(t_img *data, int x, int y)
{
	t_ray	ray;
	float	u;
	float	v;

	ray.origin = data->camera.position;
	// normalize the x and y coord to range of -1,1
	u = (2.0 * ((float)x + 0.5) / (float)IMG_WIDTH - 1.0) * data->camera.half_width;
	v = (1.0 - 2.0 * ((float)y + 0.5) / (float)IMG_HEIGHT) * data->camera.half_height;

	// calculate direction of ray
	//Ray direction = camera orientation + (u * right_vector) + (v * up_vector)
	ray.vector.x = data->camera.vector.x + (u * data->camera.right_vector.x + v) * data->camera.up_vector.x;
	ray.vector.y = data->camera.vector.y + (u * data->camera.right_vector.y + v) * data->camera.up_vector.y;
	ray.vector.z = data->camera.vector.z + (u * data->camera.right_vector.z + v) * data->camera.up_vector.z;

	// normalize the ray direction
	ray.vector = vector_Normalize(&ray.vector);
	return (ray);
}

// need a function to check whether the ray has intersect with the sphere
bool	hit_sphere(t_ray *ray, t_sphere *sphere)
{
	t_coords	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	// vector from ray origin to sphere center
	oc = vector_Subtract(&ray->origin, &sphere->position);
	a = vector_DotProduct(&ray->vector, &ray->vector);
	b = 2.0 * vector_DotProduct(&oc, &ray->vector);
	c = vector_DotProduct(&oc, &oc) - sphere->radius * sphere->radius;
	// b^2 - 4ac > 1 for it to hit
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

t_rgb trace_ray(t_ray *ray, t_img *data)
{
	t_rgb	color;
	float	closet_t;
	float	t;
	int		i;

	color.r = 1;
	color.g = 0;
	color.b = 0;
	closet_t = INFINITY;
	i = 0;
	// checks the spheres to see if the ray hits the sphere
	// need to check for planes and cylinder too
	while (i++ < data->sphere_count)
	{
		t = 0;
		if (hit_sphere(ray, &data->spheres[i]))
		{
			if (t < closet_t && t > 0)
			{
				closet_t = t;
				color = data->spheres[i].rgb;
			}
		}
	}
	return (color);
}

void	render_image(t_prog *prog, t_img *data)
{
	int		x;
	int		y;
	t_ray	ray;
	t_rgb	color;
	int		pixel_color;

	y = -1;
	while (y++ < IMG_HEIGHT)
	{
		x = -1;
		while (x++ < IMG_HEIGHT)
		{
			// get the ray direction
			ray = make_ray(data, x, y);
			// trace the ray to see if it hits the obj and which color
			color = trace_ray(&ray, &data);
			pixel_color = get_rgb((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255));
			set_img_pixel(prog->image, x, y, pixel_color);
		}
	}
	mlx_put_image_to_window(prog->mlx_ptr, prog->win_ptr, prog->image->ptr, 0, 0);
}

void	init_program(t_prog *prog, t_img *data)
{
	prog->mlx_ptr = mlx_init();
	prog->win_ptr = mlx_new_window(prog->mlx_ptr, IMG_WIDTH, IMG_HEIGHT, "MiniRT");
	prog->image = new_img(prog);
	mlx_hook(prog->win_ptr, 17,  0, handle_exit, prog);
	mlx_hook(prog->win_ptr, 2, 1L<<0, handle_keypress, prog);
	mlx_mouse_hook(prog->win_ptr, handle_mouse_click, prog);
	render_ambient(prog, data->amb_light, &data->amb_rgb);

	mlx_loop(prog->mlx_ptr);
}

void	init_img_data(t_img *data)
{
	data->error_msg = NULL;
	// ambient
	data->amb_light = 0.5;
	data->amb_rgb.r = 255;
	data->amb_rgb.g = 255;
	data->amb_rgb.b = 255;
	// camera
	data->camera.position.x = 0;
	data->camera.position.y = 0;
	data->camera.position.z = 0;
	data->camera.vector.x = 0;
	data->camera.vector.y = 0;
	data->camera.vector.z = 0;
	data->camera.fov = 0;
	// light (no rgb)
	data->light.position.x = 0;
	data->light.position.y = 0;
	data->light.position.z = 0;
	data->light.brightness = 0.0;
	// scene
	data->sphere_count = 0;
	data->plane_count = 0;
	data->cylinder_count = 0;
}
