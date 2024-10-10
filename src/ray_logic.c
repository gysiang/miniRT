/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:35:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 12:11:18 by bhowe            ###   ########.fr       */
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

t_rayparams	init_rayparams(t_data *data)
{
	t_rayparams	rp;

	rp.t = 0.01;
	rp.dl = 0;
	rp.min_dist = INFINITY;
	rp.amb_def = rgb_mul(data->amb_rgb, data->amb_light);
	rp.color_fin = rgb_get(rp.amb_def);
	return (rp);
}

int trace_ray(t_ray *ray, t_data *data)
{
	t_rayparams	rp;
	int			i;
	bool		hit;

	rp = init_rayparams(data);
	i = -1;
	hit = false;
	while (++i < data->prim_count)
	{
		ray->norm_flip = false;
		if (hit_prim(ray, data->prims[i], &rp))
		{
			if (rp.t < rp.min_dist)
			{
				rp.prim_col = data->prims[i].rgb;
				rp.min_dist = rp.t;
				rp.t_hitpoint = ray->hitpoint;
				rp.t_normal = ray->normal;
				rp.t_norm_flip = ray->norm_flip;
				hit = true;
			}
		}
	}
	if (hit)
		calc_color(data, &rp);
	return (rp.color_fin);
}
