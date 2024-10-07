/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:35:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/07 13:02:50 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// function to generate ray
// x and y are the coordinates on the image plane
t_ray	make_ray(t_data *data, int x, int y)
{
	t_ray	ray;
	float	u;
	float	v;
	t_vec	right_vec;
	t_vec	up_vec;

	ray.origin = data->camera.position;
	// get pixel coordinates
	u = (1 - 2 * (x + 0.5) / (float)IMG_WIDTH) * data->camera.scale * data->camera.aspect_ratio;
	v = (1 - 2 * (y + 0.5) / (float)IMG_HEIGHT) * data->camera.scale;
	// create rotation matrix
	right_vec = vector_Normalize(vector_CrossProduct(data->camera.vector, data->camera.up_vector));
	up_vec = vector_Normalize(vector_CrossProduct(right_vec, data->camera.vector));
	// add rotations to ray vector
	ray.vector = data->camera.vector;
	ray.vector = vector_Add(ray.vector, vector_Multiply(right_vec, u));
	ray.vector = vector_Add(ray.vector, vector_Multiply(up_vec, v));
	ray.vector = vector_Normalize(ray.vector);
	return (ray);
}

float	calculate_lighting(t_vec *hitpoint, t_vec *normal, t_light *light)
{
	t_vec	light_dir;
	float		intensity;
	// vector from intersection to light source
	light_dir = vector_Subtract(light->position, *hitpoint);
	light_dir = vector_Normalize(light_dir);
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
	i = -1;
	while (++i < data->prim_count)
	{
		if (hit_prim(ray, data->prims[i], &rp))
		{
			if (rp.t < rp.min_dist)
			{
				rp.prim_col = data->prims[i].rgb;
				rp.min_dist = rp.t;
				rp.light_intensity = calculate_lighting(&ray->hit_coord, &ray->normal, &data->light);
				// color of the sphere affected by each light
				rp.diffuse_fin = rgb_mix(rp.prim_col, rgb_mul(data->light.rgb, rp.light_intensity));
				rp.amb_fin = rgb_mix(rp.prim_col, rp.amb_def);
				// final color should be all lights added
				rp.color_fin = rgb_get(rgb_add(rp.amb_fin, rp.diffuse_fin));
			}
		}
	}
	return (rp.color_fin);
}
