/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:37:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/09 21:43:43 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec vector_create(float x, float y, float z)
{
	t_vec res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vec vector_Add(const t_vec a, const t_vec b)
{
	return (vector_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec vector_Subtract(const t_vec a, const t_vec b)
{
	return (vector_create(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec vector_Multiply(const t_vec a, float scalar)
{
	return (vector_create(a.x * scalar, a.y * scalar, a.z * scalar));
}

float vector_Length(t_vec v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// scale the vector to have a length of 1 while maintaining its direction
t_vec vector_Normalize(t_vec v)
{
	float	len;

	len = vector_Length(v);
	return (vector_create(v.x / len, v.y / len, v.z / len));
}

// helps define total length and angle of a & b
float vector_DotProduct(const t_vec a, const t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// creates perpendicular vector to a & b
t_vec vector_CrossProduct(const t_vec a, const t_vec b)
{
	t_vec	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
