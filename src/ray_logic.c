/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:35:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/02 14:50:21 by bhowe            ###   ########.fr       */
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
	ray.vector = vector_Normalize(&ray.vector);
	//printf("Ray direction: (%f, %f, %f)\n", ray.vector.x, ray.vector.y, ray.vector.z);
	return (ray);
}

// need a function to check whether the ray has intersect with the sphere
bool	hit_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_vec	oc;
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

bool	hit_prim(t_ray *ray, t_prim prim, float *t, t_rgb *col)
{
	if (prim.p_type == SP)
	{
		*col = prim.p_data.sp.rgb;
		return (hit_sphere(ray, &prim.p_data.sp, t));
	}
	return (0);
}

t_vec	intersection_point(t_ray *ray, float t)
{
	t_vec s;

	// point where the ray hits the sphere
	s.x = ray->origin.x + ray->vector.x * t;
	s.y = ray->origin.y + ray->vector.y * t;
	s.z = ray->origin.z + ray->vector.z * t;
	return (s);
}

t_vec	surface_normal(t_vec *hitpoint, t_vec pos)
{
	t_vec n;

	n = vector_Subtract(hitpoint, &pos);
	n = vector_Normalize(&n);
	return (n);
}

float	calculate_lighting(t_vec *hitpoint, t_vec *normal, t_light *light)
{
	t_vec	light_dir;
	float		intensity;
	// vector from intersection to light source
	light_dir = vector_Subtract(&light->position, hitpoint);
	light_dir = vector_Normalize(&light_dir);
	// angle between light direction and surface vector
	intensity = vector_DotProduct(&light_dir, normal);
	if (intensity < 0)
		intensity = 0;
	// scale it by the light brightness
	return (intensity * light->brightness);
}

t_rayparams	init_rayparams(t_rayparams rp, t_img *data)
{
	rp.t = 0;
	rp.min_dist = INFINITY;
	rp.amb = rgb_mul(data->amb_rgb, data->amb_light);
	return (rp);
}

/**
 * if it hits the sphere, return rgb of sphere, else return rgb of ambient.
 */
int trace_ray(t_ray *ray, t_img *data)
{
	t_rayparams	rp;
	int			color;
	int			i;

	rp = init_rayparams(rp, data);
	color = rgb_get(rp.amb);
	i = 0;
	while (i < data->prim_count)
	{
		if (hit_prim(ray, data->prims[i], &t, &prim_col))
		{
			if (t < minDistance && t > 0)
			{
				minDistance = t;
				hitpoint = intersection_point(ray, t);
				normal = surface_normal(&hitpoint, &data->spheres[i]);
				light_intensity = calculate_lighting(&hitpoint, &normal, &data->light);
				// color of the sphere affected by each light
				diffuse = rgb_mix(data->spheres[i].rgb, rgb_mul(data->light.rgb, light_intensity));
				amb = rgb_mix(data->spheres[i].rgb, amb);
				// final color should be all lights added
				color = rgb_get(rgb_add(amb, diffuse));

				/**
				 * before taking in light intensity
				 * color = rgb_get(rgb_mix(amb, data->spheres[i].rgb));
				 */
			}
		}
		i++;
	}
	return (color);
}
