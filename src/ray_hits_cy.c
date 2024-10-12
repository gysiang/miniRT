/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits_cy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:22:24 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/11 22:43:58 by bhowe            ###   ########.fr       */
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
	cyh->top_cap = false;
	cyh->bot_cap = false;
}

static bool	within_cy_height(t_cy_helper *cyh)
{
	return (cyh->y_hit >= cyh->y_min && cyh->y_hit <= cyh->y_max);
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
		cyh.hit_body = within_cy_height(&cyh);
	}
	if (cyh.hit_body)
		hit_cylinder_part(&cyh, prim, t, BODY);
	else
		check_cylinder_caps(&cyh, prim, t);
	return (cyh.hit_body || cyh.top_cap || cyh.bot_cap);
}

void	check_cylinder_caps(t_cy_helper *cyh, t_prim *prim, float *t)
{
	float	t_top;
	float	t_bot;

	cyh->top_cap = hit_disc(cyh, prim, cyh->y_max, &t_top);
	cyh->bot_cap = hit_disc(cyh, prim, cyh->y_min, &t_bot);
	if (cyh->top_cap && (!cyh->bot_cap || t_top < t_bot))
	{
		*t = t_top;
		cyh->cap_vec = prim->vector;
	}
	else if (cyh->bot_cap)
	{
		*t = t_bot;
		cyh->cap_vec = vector_multiply(prim->vector, -1);
	}
	if (cyh->top_cap || cyh->bot_cap)
		hit_cylinder_part(cyh, prim, t, CAP);
}
