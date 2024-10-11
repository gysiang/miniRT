/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_lighting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:58:49 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/11 17:59:01 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_color(t_data *data, t_rayparams *rp)
{
	t_rgb	black;

	black.r = 0;
	black.g = 0;
	black.b = 0;
	if (in_shadow(data, rp))
	{
		rp->amb_fin = rgb_mix(rp->prim_col, rp->amb_def);
		rp->color_fin = rgb_get(rgb_add(rp->amb_fin, black));
	}
	else
	{
		rp->light_intensity = calculate_lighting(rp, &data->light);
		if (data->light_count)
			rp->diffuse_fin = rgb_mix(rp->prim_col,
					rgb_mul(data->light.rgb, rp->light_intensity));
		else
			rp->diffuse_fin = black;
		rp->amb_fin = rgb_mix(rp->prim_col, rp->amb_def);
		rp->color_fin = rgb_get(rgb_add(rp->amb_fin, rp->diffuse_fin));
	}
}

float	calculate_lighting(t_rayparams *rp, t_light *light)
{
	t_vec	lv;
	float	intensity;

	lv = vector_normalize(vector_subtract(light->position, rp->t_hitpoint));
	if (vector_dotproduct(lv, rp->t_normal) > 0 && rp->t_norm_flip)
		rp->t_normal = vector_multiply(rp->t_normal, -1);
	intensity = vector_dotproduct(lv, rp->t_normal);
	if (intensity <= EPSILON)
		intensity = 0;
	return (intensity * light->brightness);
}

t_ray	create_shadow(t_data *data, t_rayparams *rp)
{
	t_ray	s;

	s.origin = vector_add(rp->t_hitpoint, rp->t_normal);
	s.vector = vector_normalize(vector_subtract(data->light.position,
				rp->t_hitpoint));
	return (s);
}

bool	in_shadow(t_data *data, t_rayparams *rp)
{
	int			i;
	t_rayparams	sp;
	t_ray		sr;
	float		dl;

	i = -1;
	sr = create_shadow(data, rp);
	dl = vector_length(vector_subtract(sr.origin, data->light.position));
	while (++i < data->prim_count)
	{
		if (i == rp->prim_num)
			continue ;
		if (hit_prim(&sr, data->prims[i], &sp))
		{
			if (sp.t > EPSILON && sp.t < dl)
				return (true);
		}
	}
	return (false);
}
