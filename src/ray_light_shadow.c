/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_light_shadow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:00:18 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/15 16:31:13 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	calculate_lighting(t_rayparams *rp, t_light *light)
{
	t_vec	lv;
	float	intensity;
	float	falloff;

	lv = vector_normalize(vector_subtract(light->position, rp->t_hitpoint));
	if (vector_dotproduct(lv, rp->t_normal) > 0 && rp->t_norm_flip)
		rp->t_normal = vector_multiply(rp->t_normal, -1);
	intensity = vector_dotproduct(lv, rp->t_normal);
	if (FALLOFF_I)
	{
		falloff = vector_length(vector_subtract(light->position,
					rp->t_hitpoint));
		falloff *= falloff;
		intensity *= FALLOFF_I / falloff;
	}
	if (intensity <= EPSILON)
		intensity = 0;
	return (intensity * light->brightness);
}

bool	in_shadow(t_data *data, t_rayparams *rp, t_light *light)
{
	int			i;
	t_rayparams	sp;
	t_ray		sr;

	sr.origin = rp->t_hitpoint;
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
