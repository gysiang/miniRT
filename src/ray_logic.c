/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:35:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/30 16:44:46 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// function to generate ray
// x and y are the coordinates on the image plane
t_ray	make_ray(t_img *data, int x, int y)
{
	t_ray	ray;

	ray.origin = data->camera.position;
	// normalize the x and y coord to range of -1,1
	ray.vector.x = (2 * (x + 0.5) / (float)IMG_WIDTH - 1) * data->camera.scale * data->camera.aspect_ratio;
	ray.vector.y = (1 - 2 * (y + 0.5) / (float)IMG_HEIGHT) * data->camera.scale;
	ray.vector.z = 1;
	//printf("u: %f\n", u);
	//printf("v: %f\n", v);

	//Ray direction = camera orientation + (u * right_vector) + (v * up_vector)
	//ray.vector.x = data->camera.vector.x + u * data->camera.right_vector.x + v * data->camera.up_vector.x;
	//ray.vector.y = data->camera.vector.y + u * data->camera.right_vector.y + v * data->camera.up_vector.y;
	//ray.vector.z = data->camera.vector.z + u * data->camera.right_vector.z + v * data->camera.up_vector.z;
	//printf("Ray direction before normalization: (%f, %f, %f)\n", ray.vector.x, ray.vector.y, ray.vector.z);

	// normalize the ray direction
	ray.vector = vector_Normalize(&ray.vector);
	//printf("Ray direction: (%f, %f, %f)\n", ray.vector.x, ray.vector.y, ray.vector.z);
	return (ray);
}

// need a function to check whether the ray has intersect with the sphere
bool	hit_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_coords	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t1;
	float		t2;
	float epsilon = 1e-4;

	// vector from ray origin to sphere center
	oc = vector_Subtract(&ray->origin, &sphere->position);
	a = vector_DotProduct(&ray->vector, &ray->vector);
	b = 2.0 * vector_DotProduct(&oc, &ray->vector);
	c = vector_DotProduct(&oc, &oc) - sphere->radius * sphere->radius;
	// b^2 - 4ac > 1 for it to hit
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return false;
	//printf("Discriminant: %f\n", discriminant);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	//printf("t1: %f, t2: %f\n", t1, t2);
	if (t1 > epsilon)
		*t = t1;
	else if (t2 > epsilon)
		*t = t2;
	else
		return false;
	//printf("Valid intersection: %f\n", *t);
	return (true);
}

/**
 * if it hits the sphere, return rgb of sphere, else return rgb of ambient.
 */
int trace_ray(t_ray *ray, t_img *data)
{
	int	color;
	float	closet_t;
	float	t;
	int		i;
	float	s;

	s = data->amb_light;
	color = get_rgb((int)(data->amb_rgb.r * s), (int)(data->amb_rgb.g * s), (int)(data->amb_rgb.b * s));
	closet_t = INFINITY;
	t = 0;
	i = 0;
	// printf("Ray origin: (%f, %f, %f), Ray direction: (%f, %f, %f)\n",
    //    ray->origin.x,
    //    ray->origin.y,
    //    ray->origin.z,
    //    ray->vector.x,
    //    ray->vector.y,
    //    ray->vector.z);
	while (i < data->sphere_count)
	{
		//printf("entered here\n");
		if (hit_sphere(ray, &data->spheres[i], &t))
		{
			if (t < closet_t && t > 0)
			{
				closet_t = t;
				color = get_rgb((int)(data->spheres[i].rgb.r), (int)(data->spheres[i].rgb.g), (int)(data->spheres[i].rgb.b));
			}
		}
		i++;
	}
	return (color);
}
