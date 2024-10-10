/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:44 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/10 16:35:16 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_prim(t_ray *ray, t_prim prim, t_rayparams *rp)
{
	if (prim.p_type == SP)
		return (hit_sphere(ray, &prim, &rp->t));
	if (prim.p_type == PL)
		return (hit_plane(ray, &prim, &rp->t));
	if (prim.p_type == CY)
		return (hit_cylinder(ray, &prim, &rp->t));
	if (prim.p_type == CN)
		return (hit_cone(ray, &prim, &rp->t));
	return (0);
}

bool	hit_sphere(t_ray *ray, t_prim *prim, float *t)
{
	t_vec	oc;
	t_qdtc	qd;

	// vector from ray origin to sphere center
	oc = vector_Subtract(ray->origin, prim->position);
	qd.a = vector_DotProduct(ray->vector, ray->vector);
	qd.b = 2.0 * vector_DotProduct(oc, ray->vector);
	qd.c = vector_DotProduct(oc, oc) - prim->p_data.sp.radius * prim->p_data.sp.radius;
	if (!do_quadratic(&qd, t))
		return (false);
	ray->hitpoint = get_hitpoint(ray->origin, ray, *t);
	ray->normal = vector_Subtract(ray->hitpoint, prim->position);
	ray->normal = vector_Normalize(ray->normal);
	return (true);
}

bool	hit_plane(t_ray *ray, t_prim *prim, float *t)
{
	float	a;
	float	b;
	t_vec	po;

	po = vector_Subtract(prim->position, ray->origin);
	a = vector_DotProduct(prim->vector, po);
	b = vector_DotProduct(prim->vector, ray->vector);
	*t = a / b;
	if (*t < EPSILON)
		return (false);
	ray->hitpoint = get_hitpoint(ray->origin, ray, *t);
	ray->normal = prim->vector;
	if (vector_DotProduct(ray->vector, ray->normal) > 0)
		ray->norm_flip = true;
	return (true);
}

bool	hit_cylinder(t_ray *ray, t_prim *prim, float *t)
{
	t_qdtc			qd;
	t_cyn_helper	cyh;

	init_cyn_helper(ray, prim, &cyh);
	qd.a = vector_DotProduct(cyh.perp, cyh.perp);
	qd.b = 2 * vector_DotProduct(cyh.perp, cyh.oc_perp);
	qd.c = vector_DotProduct(cyh.oc_perp, cyh.oc_perp) - prim->p_data.cyn.radius * prim->p_data.cyn.radius;
	// Check if ray intersects with cylinder body OR caps
	if (do_quadratic(&qd, t))
	{
		cyh.y_hit = vector_DotProduct(vector_Add(cyh.oc, vector_Multiply(cyh.ray->vector, *t)), prim->vector);
		cyh.hit_body = cyh.y_hit >= cyh.y_min && cyh.y_hit <= cyh.y_max;
	}
	if (cyh.hit_body)
		hit_cylicone_body(&cyh, prim, t);
	else
		cyh.hit_cap = hit_disc(&cyh, prim, cyh.y_min, t) || hit_disc(&cyh, prim, cyh.y_max, t);
	if (cyh.hit_cap)
		hit_cylicone_caps(&cyh, prim, t);
	return (cyh.hit_body || cyh.hit_cap);
}

bool	hit_cone(t_ray *ray, t_prim *prim, float *t)
{
	t_qdtc			qd;
	t_cyn_helper	cyh;

	init_cyn_helper(ray, prim, &cyh);
	qd.a = vector_DotProduct(cyh.perp, cyh.perp);
	qd.b = 2 * vector_DotProduct(cyh.perp, cyh.oc_perp);
	qd.c = vector_DotProduct(cyh.oc_perp, cyh.oc_perp) - prim->p_data.cyn.radius * prim->p_data.cyn.radius;
	// Check if ray intersects with cylinder body OR caps
	if (do_quadratic(&qd, t))
}
