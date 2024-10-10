/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:22:24 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 23:11:19 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cy_helper(t_ray *ray, t_prim *prim, t_cy_helper *cyh)
{
	cyh->ray = ray;
	cyh->oc = vector_subtract(ray->origin, prim->position);
	cyh->axis_proj = vector_multiply(prim->vector,
			vector_dotproduct(ray->vector, prim->vector));
	cyh->perp = vector_subtract(ray->vector, cyh->axis_proj);
	cyh->oc_perp = vector_subtract(cyh->oc, vector_multiply(prim->vector,
				vector_dotproduct(cyh->oc, prim->vector)));
	cyh->y_min = -prim->p_data.cy.height / 2;
	cyh->y_max = prim->p_data.cy.height / 2;
	cyh->hit_body = false;
	cyh->hit_cap = false;
}

void	hit_cylinder_body(t_cy_helper *cyh, t_prim *prim, float *t)
{
	cyh->ray->hitpoint = get_hitpoint(cyh->ray->origin, cyh->ray, *t);
	cyh->ray->normal = vector_subtract(cyh->ray->hitpoint, prim->position);
	cyh->ray->normal = vector_normalize(cyh->ray->normal);
}

void	hit_cylinder_caps(t_cy_helper *cyh, t_prim *prim, float *t)
{
	cyh->ray->hitpoint = get_hitpoint(cyh->ray->origin, cyh->ray, *t);
	cyh->ray->normal = prim->vector;
	cyh->ray->normal = vector_normalize(cyh->ray->normal);
}

bool	hit_cylinder(t_ray *ray, t_prim *prim, float *t)
{
	t_qdtc		qd;
	t_cy_helper	cyh;

	init_cy_helper(ray, prim, &cyh);
	qd.a = vector_dotproduct(cyh.perp, cyh.perp);
	qd.b = 2 * vector_dotproduct(cyh.perp, cyh.oc_perp);
	qd.c = vector_dotproduct(cyh.oc_perp, cyh.oc_perp)
		- prim->p_data.cy.radius * prim->p_data.cy.radius;
	if (do_quadratic(&qd, t))
	{
		cyh.y_hit = vector_dotproduct(vector_add(cyh.oc,
					vector_multiply(cyh.ray->vector, *t)), prim->vector);
		cyh.hit_body = cyh.y_hit >= cyh.y_min && cyh.y_hit <= cyh.y_max;
	}
	if (cyh.hit_body)
		hit_cylinder_body(&cyh, prim, t);
	else
	{
		cyh.hit_cap = hit_disc(&cyh, prim, cyh.y_min, t)
			|| hit_disc(&cyh, prim, cyh.y_max, t);
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
