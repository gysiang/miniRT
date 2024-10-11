/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:44 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/11 10:01:50 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_hitpoint(t_vec origin, t_ray *ray, float t)
{
	return (vector_add(origin, vector_multiply(ray->vector, t)));
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
	t_qdtc		qd;

	oc = vector_subtract(ray->origin, prim->position);
	qd.a = vector_dotproduct(ray->vector, ray->vector);
	qd.b = 2.0 * vector_dotproduct(oc, ray->vector);
	qd.c = vector_dotproduct(oc, oc)
		- prim->p_data.sp.radius * prim->p_data.sp.radius;
	if (!do_quadratic(&qd, t))
		return (false);
	ray->hitpoint = get_hitpoint(ray->origin, ray, *t);
	ray->normal = vector_subtract(ray->hitpoint, prim->position);
	ray->normal = vector_normalize(ray->normal);
	return (true);
}

bool	hit_plane(t_ray *ray, t_prim *prim, float *t)
{
	float	a;
	float	b;
	t_vec	po;

	po = vector_subtract(prim->position, ray->origin);
	a = vector_dotproduct(prim->vector, po);
	b = vector_dotproduct(prim->vector, ray->vector);
	*t = a / b;
	if (*t < EPSILON)
		return (false);
	ray->hitpoint = get_hitpoint(ray->origin, ray, *t);
	ray->normal = prim->vector;
	if (vector_dotproduct(ray->vector, ray->normal) > 0)
		ray->norm_flip = true;
	return (true);
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
