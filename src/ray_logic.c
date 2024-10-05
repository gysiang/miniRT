/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:35:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/04 20:42:07 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// function to generate ray
// x and y are the coordinates on the image plane
t_ray	make_ray(t_data *data, int x, int y)
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

t_vec	intersection_point(t_ray *ray, float t)
{
	t_vec s;

	// point where the ray hits the prim
	s.x = ray->origin.x + ray->vector.x * t;
	s.y = ray->origin.y + ray->vector.y * t;
	s.z = ray->origin.z + ray->vector.z * t;
	return (s);
}

t_vec	surface_normal(t_vec *hitpoint, t_vec pos, t_type type)
{
	t_vec n;

	if (type != PL)
	{
		n = vector_Subtract(*hitpoint, pos);
		n = vector_Normalize(&n);
	}
	else
		n = pos;
	return (n);
}

float	calculate_lighting(t_vec *hitpoint, t_vec *normal, t_light *light)
{
	t_vec	light_dir;
	float		intensity;
	// vector from intersection to light source
	light_dir = vector_Subtract(light->position, *hitpoint);
	light_dir = vector_Normalize(&light_dir);
	// angle between light direction and surface vector
	intensity = vector_DotProduct(light_dir, *normal);
	if (intensity < 0)
		intensity = 0;
	// scale it by the light brightness
	return (intensity * light->brightness);
}

t_rayparams	init_rayparams(t_data *data)
{
	t_rayparams	rp;

	rp.t = 0;
	rp.min_dist = INFINITY;
	rp.amb_def = rgb_mul(data->amb_rgb, data->amb_light);
	rp.color_fin = rgb_get(rp.amb_def);
	return (rp);
}

/**
 * if it hits the sphere, return rgb of sphere, else return rgb of ambient.
 */
int trace_ray(t_ray *ray, t_data *data)
{
	t_rayparams	rp;
	int			i;

	rp = init_rayparams(data);
	i = 0;
	while (i < data->prim_count)
	{
		if (hit_prim(ray, data->prims[i], &rp))
		{
			if (rp.t < rp.min_dist)
			{
				rp.min_dist = rp.t;
				rp.hitpoint = intersection_point(ray, rp.t);
				rp.normal = surface_normal(&rp.hitpoint, rp.prim_pos, data->prims[i].p_type);
				rp.light_intensity = calculate_lighting(&rp.hitpoint, &rp.normal, &data->light);
				// color of the sphere affected by each light
				rp.diffuse_fin = rgb_mix(rp.prim_col, rgb_mul(data->light.rgb, rp.light_intensity));
				rp.amb_fin = rgb_mix(rp.prim_col, rp.amb_def);
				// final color should be all lights added
				rp.color_fin = rgb_get(rgb_add(rp.amb_fin, rp.diffuse_fin));
			}
		}
		i++;
	}
	return (rp.color_fin);
}
