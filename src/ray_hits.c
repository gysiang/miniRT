/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:44 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/04 11:55:10 by bhowe            ###   ########.fr       */
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

bool	hit_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	t_vec		oc;
	t_qdtc	qd;

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

t_matrix transpose_matrix(const t_matrix *matrix)
{
	t_matrix transposed;

	transposed.m[0] = vector_create(matrix->m[0].x, matrix->m[1].x, matrix->m[2].x);
	transposed.m[1] = vector_create(matrix->m[0].y, matrix->m[1].y, matrix->m[2].y);
	transposed.m[2] = vector_create(matrix->m[0].z, matrix->m[1].z, matrix->m[2].z);
	return (transposed);
}

t_matrix	rot_matrix_create(t_vec rot_vector, float rot_angle)
{
	t_matrix	rot_matrix;
	float		cos_theta;
	float		sin_theta;

	rot_vector = vector_Normalize(&rot_vector);
	cos_theta = cos(rot_angle);
	sin_theta = sin(rot_angle);
	rot_matrix.m[0] = vector_create(cos_theta + rot_vector.x * rot_vector.x * (1 - cos_theta),
		rot_vector.x * rot_vector.y * (1 - cos_theta) - rot_vector.z * sin_theta,
		rot_vector.x * rot_vector.z * (1 - cos_theta) + rot_vector.y * sin_theta);
	rot_matrix.m[1] = vector_create(rot_vector.x * rot_vector.y * (1 - cos_theta) + rot_vector.z * sin_theta,
		cos_theta + rot_vector.y * rot_vector.y * (1 - cos_theta),
		rot_vector.y * rot_vector.z * (1 - cos_theta) - rot_vector.x * sin_theta);
	rot_matrix.m[2] = vector_create(rot_vector.x * rot_vector.z * (1 - cos_theta) - rot_vector.y * sin_theta,
		rot_vector.y * rot_vector.z * (1 - cos_theta) + rot_vector.x * sin_theta,
		cos_theta + rot_vector.z * rot_vector.z * (1 - cos_theta));
	rot_matrix = transpose_matrix(&rot_matrix);
	return (rot_matrix);
}

void	ray_rotate(t_ray *ray, t_vec *cy_vector)
{
	t_vec		y_axis;
	t_vec		rot_vector;
	float		rot_angle;
	t_matrix	rot_matrix;

	y_axis = vector_create(0.0, 1.0, 0.0);
	rot_vector = vector_CrossProduct(&y_axis, cy_vector);
	rot_angle = acos(vector_DotProduct(&y_axis, cy_vector));
	rot_matrix = rot_matrix_create(rot_vector, rot_angle);
	ray->origin = vector_create(rot_matrix.m[0].x * ray->origin.x + rot_matrix.m[0].y * ray->origin.y + rot_matrix.m[0].z * ray->origin.z,
		rot_matrix.m[1].x * ray->origin.x + rot_matrix.m[1].y * ray->origin.y + rot_matrix.m[1].z * ray->origin.z,
		rot_matrix.m[2].x * ray->origin.x + rot_matrix.m[2].y * ray->origin.y + rot_matrix.m[2].z * ray->origin.z);
	ray->vector = vector_create(rot_matrix.m[0].x * ray->vector.x + rot_matrix.m[0].y * ray->vector.y + rot_matrix.m[0].z * ray->vector.z,
		rot_matrix.m[1].x * ray->vector.x + rot_matrix.m[1].y * ray->vector.y + rot_matrix.m[1].z * ray->vector.z,
		rot_matrix.m[2].x * ray->vector.x + rot_matrix.m[2].y * ray->vector.y + rot_matrix.m[2].z * ray->vector.z);
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

bool	hit_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	t_qdtc		qd;
	t_cy_helper	cyh;

	ray_rotate(ray, &cylinder->vector);
	cyh.radius = cylinder->radius;
	cyh.cy_x = ray->origin.x - cylinder->position.x;
	cyh.cy_z = ray->origin.z - cylinder->position.z;
	qd.a = ray->vector.x * ray->vector.x + ray->vector.z * ray->vector.z;
	qd.b = 2 * (cyh.cy_x * ray->vector.x + cyh.cy_z * ray->vector.z);
	qd.c = cyh.cy_x * cyh.cy_x + cyh.cy_z * cyh.cy_z - cyh.radius * cyh.radius;
	if (!do_quadratic(&qd, t))
		return (false);
	// Check if ray is within the height of the cylinder
	cyh.y_min = cylinder->position.y - cylinder->height / 2;
	cyh.y_max = cylinder->position.y + cylinder->height / 2;
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
