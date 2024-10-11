/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits_cy1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:51:58 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/11 18:52:22 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_cylinder_part(t_cy_helper *cyh, t_prim *prim, float *t, int part)
{
	cyh->ray->hitpoint = get_hitpoint(cyh->ray->origin, cyh->ray, *t);
	if (part == BODY)
		cyh->ray->normal = vector_subtract(cyh->ray->hitpoint, prim->position);
	else
		cyh->ray->normal = cyh->cap_vec;
	cyh->ray->normal = vector_normalize(cyh->ray->normal);
}

bool	hit_disc(t_cy_helper *cyh, t_prim *prim, float y_offset, float *t)
{
	t_prim	temp;
	float	t_cap;
	t_vec	v;
	t_vec	p;

	temp.position = vector_add(prim->position,
			vector_multiply(prim->vector, y_offset));
	temp.vector = prim->vector;
	if (y_offset < 0)
		temp.vector = vector_multiply(prim->vector, -1);
	temp.vector = vector_normalize(temp.vector);
	if (hit_plane(cyh->ray, &temp, &t_cap))
	{
		p = vector_add(cyh->ray->origin,
				vector_multiply(cyh->ray->vector, t_cap));
		v = vector_subtract(p, temp.position);
		if (vector_dotproduct(v, v) <= prim->p_data.cy.radius
			* prim->p_data.cy.radius && t_cap > EPSILON)
			return (*t = t_cap, cyh->cap_vec = temp.vector, true);
	}
	return (false);
}
