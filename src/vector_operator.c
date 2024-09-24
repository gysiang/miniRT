/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:25:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/24 11:10:30 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// vector add
t_coords vector_Add(const t_coords *a, const t_coords *b)
{
	t_coords result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}

// vector subtract
t_coords vector_Subtract(const t_coords *a, const t_coords *b)
{
	t_coords result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;	return (result);
}

// scale the vector to have a length of 1 while maintaining its direction
t_coords vector_Normalize(const t_coords *v)
{
	float		len;
	t_coords	result;

	len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	result.x = v->x / len;
	result.y = v->y / len;
	result.z = v->z / len;
}

// cross product, results in a vector that is perperndicular to both vector a and
t_coords vector_CrossProduct(const t_coords *a, const t_coords *b)
{
	t_coords	result;

	result.x = a->y * b->z - a->z * b->y;
	result.y = a->z * b->x - a->x * b->z;
	result.z = a->x * b->y - a->y * b->x;
	return (result);
}
