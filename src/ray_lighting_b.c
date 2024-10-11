/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_lighting_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:58:49 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/11 17:30:26 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	add_lighting(t_rayparams *rp, t_light *l)
{
	rp->light_intensity = calculate_lighting(rp, l);
	rp->color_temp = rgb_mix(rp->prim_col,
				rgb_mul(l->rgb, rp->light_intensity));
	if (rp->first_light_calc)
	{
		rp->first_light_calc = false;
		return (rp->color_temp);
	}
	return (rgb_mix(rp->diffuse_fin, rp->color_temp));
}

void	calc_color(t_data *data, t_rayparams *rp)
{
	t_rgb	black;
	int		i;

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
		i = -1;
		while (++i < data->light_count)
			rp->diffuse_fin = add_lighting(rp, &data->light_arr[i]);
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
