/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:37:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/06 21:21:16 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// vector add
t_vec vector_Add(const t_vec a, const t_vec b)
{
	t_vec result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

// vector subtract
t_vec vector_Subtract(const t_vec a, const t_vec b)
{
	t_vec result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec vector_Multiply(const t_vec a, float scalar)
{
	t_vec result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

// measures of parrallel the two vectors are
float vector_DotProduct(const t_vec a, const t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// scale the vector to have a length of 1 while maintaining its direction
t_vec vector_Normalize(const t_vec *v)
{
	float		len;
	t_vec	result;

	len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	result.x = v->x / len;
	result.y = v->y / len;
	result.z = v->z / len;

	return (result);
}

// cross product, results in a vector that is perperndicular to both vector a and
t_vec vector_CrossProduct(const t_vec a, const t_vec b)
{
	t_vec	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec vector_create(float x, float y, float z)
{
	t_vec res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}
