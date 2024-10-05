/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:44 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/06 02:19:26 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	do_quadratic(t_qdtc *qd, float *t)
{
	qd->discrim = qd->b * qd->b - 4 * qd->a * qd->c;
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
	oc = vector_Subtract(&ray->origin, &prim->position);
	qd.a = vector_DotProduct(&ray->vector, &ray->vector);
	qd.b = 2.0 * vector_DotProduct(&oc, &ray->vector);
	qd.c = vector_DotProduct(&oc, &oc) - prim->p_data.sp.radius * prim->p_data.sp.radius;
	return (do_quadratic(&qd, t));
}

bool	hit_plane(t_ray *ray, t_prim *prim, float *t)
{
	float	a;
	float	b;
	t_vec	po;

	po = vector_Subtract(&prim->position, &ray->origin);
	a = vector_DotProduct(&prim->vector, &po);
	b = vector_DotProduct(&prim->vector, &ray->vector);
	*t = a / b;
	if (*t > EPSILON)
		return (true);
	return (false);
}

bool	check_cylinder_caps(t_qdtc *qd, t_ray *ray, t_cy_helper *cyh, float *t)
{
	float	cap_x;
	float	cap_z;

	cap_x = cyh->cy_x + qd->t1 * ray->vector.x;
	cap_z = cyh->cy_z + qd->t1 * ray->vector.z;
	cyh->radius *= cyh->radius;
	if (cap_x * cap_x + cap_z * cap_z <= cyh->radius)
	{
		*t = qd->t1;
		return (true);
	}
	cap_x = cyh->cy_x + qd->t2 * ray->vector.x;
	cap_z = cyh->cy_z + qd->t2 * ray->vector.z;
	if (cap_x * cap_x + cap_z * cap_z <= cyh->radius)
	{
		*t = qd->t2;
		return (true);
	}
	return (false);
}

bool	hit_cylinder(t_ray *ray, t_prim *prim, float *t)
{
	t_qdtc		qd;
	t_cy_helper	cyh;

	cyh.radius = prim->p_data.cy.radius;
	cyh.cy_x = ray->origin.x - prim->position.x;
	cyh.cy_z = ray->origin.z - prim->position.z;
	qd.a = ray->vector.x * ray->vector.x + ray->vector.z * ray->vector.z;
	qd.b = 2 * (cyh.cy_x * ray->vector.x + cyh.cy_z * ray->vector.z);
	qd.c = cyh.cy_x * cyh.cy_x + cyh.cy_z * cyh.cy_z - cyh.radius * cyh.radius;
	if (!do_quadratic(&qd, t))
		return (false);
	// Check if ray is within the height of the cylinder
	cyh.y_min = prim->position.y - prim->p_data.cy.height / 2;
	cyh.y_max = prim->position.y + prim->p_data.cy.height / 2;
	cyh.y_hit = ray->origin.y + *t * ray->vector.y;
	if (cyh.y_hit >= cyh.y_min && cyh.y_hit <= cyh.y_max)
		return (true);
	// Check if ray hits the caps instead
	qd.t1 = (cyh.y_min - ray->origin.y) / ray->vector.y;
	qd.t2 = (cyh.y_max - ray->origin.y) / ray->vector.y;
	return (check_cylinder_caps(&qd, ray, &cyh, t));
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
