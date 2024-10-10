/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits_cylicone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:48:16 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/10 15:00:04 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_disc(t_cyn_helper *cyh, t_prim *prim, float y_offset, float *t)
{
	t_prim	temp;
	float	t_cap;
	t_vec	v;
	t_vec	p;

	temp.position = vector_Add(prim->position, vector_Multiply(prim->vector, y_offset));
	temp.vector = prim->vector;
	if (y_offset < 0)
		temp.vector = vector_Multiply(prim->vector, -1);
	temp.vector = vector_Normalize(temp.vector);
	if (hit_plane(cyh->ray, &temp, &t_cap))
	{
		p = vector_Add(cyh->ray->origin, vector_Multiply(cyh->ray->vector, t_cap));
		v = vector_Subtract(p, temp.position);
		if (vector_DotProduct(v, v) <= prim->p_data.cyn.radius * prim->p_data.cyn.radius && t_cap > EPSILON)
		{
			cyh->top_cap = y_offset > 0;
			*t = t_cap;
			return (true);
		}
	}
	return (false);
}

void	init_cyn_helper(t_ray *ray, t_prim *prim, t_cyn_helper *cyh)
{
	cyh->ray = ray;
	// Vector from ray origin to cylinder center
	cyh->oc = vector_Subtract(ray->origin, prim->position);
	// Project ray direction and oc onto cylinder axis
	cyh->axis_proj = vector_Multiply(prim->vector, vector_DotProduct(ray->vector, prim->vector));
	// Calculate perpendicular components
	cyh->perp = vector_Subtract(ray->vector, cyh->axis_proj);
	cyh->oc_perp = vector_Subtract(cyh->oc, vector_Multiply(prim->vector, vector_DotProduct(cyh->oc, prim->vector)));
	// Set cylinder height limits
	cyh->y_min = -prim->p_data.cyn.height / 2;
	cyh->y_max = prim->p_data.cyn.height / 2;
	cyh->hit_body = false;
	cyh->hit_cap = false;
}

void	hit_cylicone_body(t_cyn_helper *cyh, t_prim *prim, float *t)
{
	cyh->ray->hitpoint = get_hitpoint(cyh->ray->origin, cyh->ray, *t);
	cyh->ray->normal = vector_Subtract(cyh->ray->hitpoint, prim->position);
	cyh->ray->normal = vector_Normalize(cyh->ray->normal);
}

void	hit_cylicone_caps(t_cyn_helper *cyh, t_prim *prim, float *t)
{
	cyh->ray->hitpoint = get_hitpoint(cyh->ray->origin, cyh->ray, *t);
	cyh->ray->normal = prim->vector;
	cyh->ray->normal = vector_Normalize(cyh->ray->normal);
}


