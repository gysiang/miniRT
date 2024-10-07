/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:28:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/07 10:29:23 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec matrix_multiply_vector(matrix4x4 *mat, t_vec *v)
{
	 t_vec result;

	result.x = mat->m[0][0] * v->x + mat->m[0][1] * v->y + mat->m[0][2] * v->z + mat->m[0][3];
	result.y = mat->m[1][0] * v->x + mat->m[1][1] * v->y + mat->m[1][2] * v->z + mat->m[1][3];
	result.z = mat->m[2][0] * v->x + mat->m[2][1] * v->y + mat->m[2][2] * v->z + mat->m[2][3];
	return (result);
}

matrix4x4 create_camera_to_world_matrix(t_vec position, t_vec forward, t_vec up)
{
	matrix4x4 mat;
	t_vec right;

	right = vector_CrossProduct(forward, up);
	right = vector_Normalize(&right);

	mat.m[0][0] = right.x;
	mat.m[0][1] = right.y;
	mat.m[0][2] = right.z;
	mat.m[0][3] = 0;

	mat.m[1][0] = up.x;
	mat.m[1][1] = up.y;
	mat.m[1][2] = up.z;
	mat.m[1][3] = 0;

	mat.m[2][0] = forward.x;
	mat.m[2][1] = forward.y;
	mat.m[2][2] = forward.z;
	mat.m[2][3] = 0;

	// Set the translation part (camera position)
	mat.m[0][3] = position.x;
	mat.m[1][3] = position.y;
	mat.m[2][3] = position.z;
	mat.m[3][0] = 0;
	mat.m[3][1] = 0;
	mat.m[3][2] = 0;
	mat.m[3][3] = 1;
	return (mat);
}
