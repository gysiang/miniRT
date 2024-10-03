/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:44 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/03 16:59:01 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	do_quadratic(t_quadratic *qd, float *t)
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

bool	hit_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_vec		oc;
	t_quadratic	qd;

	// vector from ray origin to sphere center
	oc = vector_Subtract(&ray->origin, &sphere->position);
	qd.a = vector_DotProduct(&ray->vector, &ray->vector);
	qd.b = 2.0 * vector_DotProduct(&oc, &ray->vector);
	qd.c = vector_DotProduct(&oc, &oc) - sphere->radius * sphere->radius;
	return (do_quadratic(&qd, t));
}

bool	hit_plane(t_ray *ray, t_plane *plane, float *t)
{
	float	a;
	float	b;
	t_vec	po;

	po = vector_Subtract(&plane->position, &ray->origin);
	a = vector_DotProduct(&plane->vector, &po);
	b = vector_DotProduct(&plane->vector, &ray->vector);
	*t = a / b;
	if (*t > EPSILON)
		return (true);
	return (false);
}

bool	check_cylinder_height(t_ray *ray, t_cylinder *cylinder, float *t)
{
	float	y_min;
	float	y_max;
	float	y_hit;

	y_min = cylinder->position.y - cylinder->height / 2;
	y_max = cylinder->position.y + cylinder->height / 2;
	y_hit = ray->origin.y + *t * ray->vector.y;
	if (y_hit >= y_min && y_hit <= y_max)
		return (true);
	return (false);
}

bool	hit_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	t_quadratic	qd;
	int			c_x;
	int			c_z;

	c_x = ray->origin.x - cylinder->position.x;
	c_z = ray->origin.z - cylinder->position.z;
	qd.a = ray->vector.x * ray->vector.x + ray->vector.z * ray->vector.z;
	qd.b = 2 * (c_x * ray->vector.x + c_z * ray->vector.z);
	qd.c = c_x * c_x + c_z * c_z - cylinder->radius * cylinder->radius;
	if (!do_quadratic(&qd, t))
		return (false);
	return (check_cylinder_height(ray, cylinder, t));
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
		return (hit_plane(ray, &prim.p_data.pl, &rp->t));
	}
	if (prim.p_type == CY)
	{
		rp->prim_col = prim.p_data.cy.rgb;
		rp->prim_pos = prim.p_data.cy.vector;
		return (hit_cylinder(ray, &prim.p_data.cy, &rp->t));
	}
	return (0);
}
