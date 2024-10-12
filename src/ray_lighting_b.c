/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_lighting_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:58:49 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/11 23:54:31 by bhowe            ###   ########.fr       */
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
	return (rgb_add(rp->diffuse_fin, rp->color_temp));
}

t_rgb	add_shadow(t_rayparams *rp)
{
	if (rp->first_light_calc)
	{
		rp->first_light_calc = false;
		return (rp->amb_fin);
	}
	return (rgb_mix(rp->diffuse_fin, rp->amb_fin));
}

void	calc_color(t_data *data, t_rayparams *rp)
{
	int		i;

	rp->amb_fin = rgb_mix(rp->prim_col, rp->amb_def);
	rp->color_fin = rgb_get(rp->amb_fin);
	if (!data->light_count)
		return ;
	i = -1;
	while (++i < data->light_count)
	{
		if (!in_shadow(data, rp, &data->light_arr[i]))
			rp->diffuse_fin = add_lighting(rp, &data->light_arr[i]);
		else
			rp->diffuse_fin = add_shadow(rp);
	}
	rp->color_fin = rgb_get(rgb_add(rp->amb_fin, rp->diffuse_fin));
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

bool	in_shadow(t_data *data, t_rayparams *rp, t_light *light)
{
	int			i;
	t_rayparams	sp;
	t_ray		sr;

	sr.origin = vector_add(rp->t_hitpoint, rp->t_normal);
	sr.vector = vector_normalize(vector_subtract(light->position,
				rp->t_hitpoint));
	rp->dl = vector_length(vector_subtract(sr.origin, light->position));
	i = -1;
	while (++i < data->prim_count)
	{
		if (i == rp->prim_num)
			continue ;
		if (hit_prim(&sr, data->prims[i], &sp))
		{
			if (sp.t > EPSILON && sp.t < rp->dl)
				return (true);
		}
	}
	return (false);
}
