/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:33:16 by bhowe             #+#    #+#             */
/*   Updated: 2024/09/20 16:38:32 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_discr(t_ray *ray, t_sphere *sp, t_qdtrc *q)
{
	q->a = vec_dot(ray->dir, ray->dir);
	q->dist = vec_sub(ray->origin, sp->position);
	q->b = 2 * vec_dot(ray->dir, q->dist);
	q->c = vec_dot(q->dist, q->dist) - (sp->diameter * sp->diameter / 4);
	return (q->b * q->b - 4 * q->a * q->c);
}

/*	The first half is just quadratic formula.
	The goal is to get the shortest intersecting distance
	and store it in the equivalent ray */

int	intersect(t_ray *ray, t_sphere *sp)
{
	t_qdtrc	q;
	float	discr;
	float	discr_sqrt;
	float	t0;
	float	t1;

	discr = get_discr(ray, sp, &q);
	if (discr < 0)
		return (0);
	else
	{
		discr_sqrt = sqrtf(discr);
		t0 = (-q.b + discr_sqrt) / 2;
		t1 = (-q.b - discr_sqrt) / 2;
		if (t0 > t1)
			t0 = t1;
		if (t0 > 0.0f && t0 < ray->t)
			return (ray->t = t0, 1);
	}
	return (0);
}

/*	(x, y) is the ray pos in screen space
	(as opposed to window coord) */
t_ray	gen_ray(int i, int j)
{
	float	x;
	float	y;
	float	aspect_ratio;

	aspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
	x = (2 * (i + 0.5) / WINDOW_WIDTH - 1);
	y = (1 - 2 * (j + 0.5) / WINDOW_HEIGHT) / aspect_ratio;

}


// Every pixel will shoot a ray
void	trace_rays(t_prog *prog, t_img *data)
{
	int		x;
	int		y;
	t_ray	ray;

	prog->image = new_img(prog);
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			ray = gen_ray(x, y);
			if (intersect(&ray, &data->sphere))
				set_img_pixel(prog->image, x, y, get_rgb(data->sphere.rgb));
		}
	}
}
