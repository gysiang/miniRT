/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:44 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/03 11:09:08 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_vec	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t1;
	float		t2;

	// vector from ray origin to sphere center
	oc = vector_Subtract(&ray->origin, &sphere->position);
	a = vector_DotProduct(&ray->vector, &ray->vector);
	b = 2.0 * vector_DotProduct(&oc, &ray->vector);
	c = vector_DotProduct(&oc, &oc) - sphere->radius * sphere->radius;
	// b^2 - 4ac > 1 for it to hit
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return false;
	//printf("Discriminant: %f\n", discriminant);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	//printf("t1: %f, t2: %f\n", t1, t2);
	if (t1 > EPSILON)
		*t = t1;
	else if (t2 > EPSILON)
		*t = t2;
	else
		return false;
	//printf("Valid intersection: %f\n", *t);
	return (true);
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

// bool	hit_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
// {
// 	return (false);
// }

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
	return (0);
}
