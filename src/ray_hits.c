/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:44 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/09 13:42:53 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_hitpoint(t_vec origin, t_ray *ray, float t)
{
	return (vector_Add(origin, vector_Multiply(ray->vector, t)));
}

bool	do_quadratic(t_qdtc *qd, float *t)
{
	qd->discrim = qd->b * qd->b - 4 * qd->a * qd->c;
	if (qd->discrim < 0)
		return (false);
	qd->discrim_sqrt = sqrt(qd->discrim);
	qd->t1 = (-qd->b - qd->discrim_sqrt) / (2.0 * qd->a);
	qd->t2 = (-qd->b + qd->discrim_sqrt) / (2.0 * qd->a);
	if (qd->t1 > EPSILON)
		*t = qd->t1;
	else if (qd->t2 > EPSILON)
		*t = qd->t2;
	else
		return (false);
	return (true);
}

bool	hit_sphere(t_ray *ray, t_prim *prim, float *t)
{
	t_vec		oc;
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
	return (true);
}

bool	hit_disc(t_cy_helper *cyh, t_prim *prim, float y_offset, float *t)
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
		if (vector_DotProduct(v, v) <= prim->p_data.cy.radius * prim->p_data.cy.radius && t_cap > EPSILON)
		{
			cyh->top_cap = y_offset > 0;
			*t = t_cap;
			return (true);
		}
	}
	return (false);
}

void	init_cy_helper(t_ray *ray, t_prim *prim, t_cy_helper *cyh)
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
	cyh->y_min = -prim->p_data.cy.height / 2;
	cyh->y_max = prim->p_data.cy.height / 2;
	cyh->hit_body = false;
	cyh->hit_cap = false;
}

void	hit_cylinder_body(t_cy_helper *cyh, t_prim *prim, float *t)
{
	cyh->ray->hitpoint = get_hitpoint(cyh->ray->origin, cyh->ray, *t);
	cyh->ray->normal = vector_Subtract(cyh->ray->hitpoint, prim->position);
	cyh->ray->normal = vector_Normalize(cyh->ray->normal);
}

void	hit_cylinder_caps(t_cy_helper *cyh, t_prim *prim, float *t)
{
	cyh->ray->hitpoint = get_hitpoint(cyh->ray->origin, cyh->ray, *t);
	cyh->ray->normal = prim->vector;
	if (!cyh->top_cap)
		cyh->ray->normal = vector_Multiply(prim->vector, -1);
	cyh->ray->normal = vector_Normalize(cyh->ray->normal);
}

bool	hit_cylinder(t_ray *ray, t_prim *prim, float *t)
{
	t_qdtc qd;
	t_cy_helper cyh;

	init_cy_helper(ray, prim, &cyh);
	qd.a = vector_DotProduct(cyh.perp, cyh.perp);
	qd.b = 2 * vector_DotProduct(cyh.perp, cyh.oc_perp);
	qd.c = vector_DotProduct(cyh.oc_perp, cyh.oc_perp) - prim->p_data.cy.radius * prim->p_data.cy.radius;
	// Check if ray intersects with cylinder body OR caps
	if (do_quadratic(&qd, t))
	{
		cyh.y_hit = vector_DotProduct(vector_Add(cyh.oc, vector_Multiply(cyh.ray->vector, *t)), prim->vector);
		cyh.hit_body = cyh.y_hit >= cyh.y_min && cyh.y_hit <= cyh.y_max;
	}
	if (cyh.hit_body)
		hit_cylinder_body(&cyh, prim, t);
	else
	{
		cyh.hit_cap = hit_disc(&cyh, prim, cyh.y_min, t) || hit_disc(&cyh, prim, cyh.y_max, t);
		if (cyh.hit_cap)
			hit_cylinder_caps(&cyh, prim, t);
	}
	return (cyh.hit_body || cyh.hit_cap);
}

bool	hit_prim(t_ray *ray, t_prim prim, t_rayparams *rp)
{
	if (prim.p_type == SP)
		return (hit_sphere(ray, &prim, &rp->t));
	if (prim.p_type == PL)
		return (hit_plane(ray, &prim, &rp->t));
	if (prim.p_type == CY)
		return (hit_cylinder(ray, &prim, &rp->t));
	return (0);
}
