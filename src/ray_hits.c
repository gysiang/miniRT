/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:44 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/05 22:02:56 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

bool	hit_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_vec		oc;
	t_qdtc	qd;

	// vector from ray origin to sphere center
	oc = vector_Subtract(ray->origin, sphere->position);
	qd.a = vector_DotProduct(ray->vector, ray->vector);
	qd.b = 2.0 * vector_DotProduct(oc, ray->vector);
	qd.c = vector_DotProduct(oc, oc) - sphere->radius * sphere->radius;
	return (do_quadratic(&qd, t));
}

bool	hit_plane(t_ray *ray, t_vec pos, t_vec vector, float *t)
{
	float	a;
	float	b;
	t_vec	po;

	po = vector_Subtract(pos, ray->origin);
	a = vector_DotProduct(vector, po);
	b = vector_DotProduct(vector, ray->vector);
	*t = a / b;
	if (*t > EPSILON)
		return (true);
	return (false);
}

bool	hit_disc(t_ray *ray, t_cy_helper *cyh, float y_offset, float *t)
{
	float	t_mem;
	float	d2;
	t_vec	v;
	t_vec	p;

	t_mem = *t;
	cyh->cap_center = vector_Add(cyh->cylinder->position, vector_Multiply(cyh->cylinder->vector, y_offset));
	if (hit_plane(ray, cyh->cap_center, cyh->cylinder->vector, &t_mem))
	{
		p = vector_Add(ray->origin, vector_Multiply(ray->vector, t_mem));
		v = vector_Subtract(p, cyh->cap_center);
		d2 = vector_DotProduct(v, v);
		if (d2 <= cyh->cylinder->radius * cyh->cylinder->radius && t_mem < *t - EPSILON)
		{
			*t = t_mem;
			return (true);
		}
	}
	return (false);
}

void	init_cy_helper(t_ray *ray, t_cylinder *cylinder, t_cy_helper *cyh)
{
	cyh->ray = ray;
	cyh->cylinder = cylinder;
	// Vector from ray origin to cylinder center
	cyh->oc = vector_Subtract(ray->origin, cylinder->position);
	// Project ray direction and oc onto cylinder axis
	cyh->axis_proj = vector_Multiply(cylinder->vector, vector_DotProduct(ray->vector, cylinder->vector));
	// Calculate perpendicular components
	cyh->perp = vector_Subtract(ray->vector, cyh->axis_proj);
	cyh->oc_perp = vector_Subtract(cyh->oc, vector_Multiply(cylinder->vector, vector_DotProduct(cyh->oc, cylinder->vector)));
}

bool	hit_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	bool	hit_body;
	bool	hit_cap;
	t_qdtc qd;
	t_cy_helper cyh;

	init_cy_helper(ray, cylinder, &cyh);
	qd.a = vector_DotProduct(cyh.perp, cyh.perp);
	qd.b = 2 * vector_DotProduct(cyh.perp, cyh.oc_perp);
	qd.c = vector_DotProduct(cyh.oc_perp, cyh.oc_perp) - cylinder->radius * cylinder->radius;
	if (!do_quadratic(&qd, t))
		return (false);
	// Check if intersection is within cylinder height
	cyh.y_hit = vector_DotProduct(vector_Add(cyh.oc, vector_Multiply(ray->vector, *t)), cylinder->vector);
	cyh.y_min = -cylinder->height / 2;
	cyh.y_max = cylinder->height / 2;
	hit_body = cyh.y_hit >= cyh.y_min && cyh.y_hit <= cyh.y_max;
	// Check if intersection is within cylinder caps
	hit_cap = hit_disc(ray, &cyh, cyh.y_min, t) || hit_disc(ray, &cyh, cyh.y_max, t);
	return (hit_body || hit_cap);
}

bool	hit_prim(t_ray *ray, t_prim prim, t_rayparams *rp)
{
	if (prim.p_type == SP)
	{
		rp->prim_col = prim.p_data.sp.rgb;
		rp->prim_pos = prim.p_data.sp.position;
		return (hit_sphere(ray, &prim.p_data.sp, &rp->t));
	}
	if (prim.p_type == PL)
	{
		rp->prim_col = prim.p_data.pl.rgb;
		rp->prim_pos = prim.p_data.pl.vector;
		return (hit_plane(ray, prim.p_data.pl.position, prim.p_data.pl.vector, &rp->t));
	}
	if (prim.p_type == CY)
	{
		rp->prim_col = prim.p_data.cy.rgb;
		rp->prim_pos = prim.p_data.cy.vector;
		return (hit_cylinder(ray, &prim.p_data.cy, &rp->t));
	}
	return (0);
}
