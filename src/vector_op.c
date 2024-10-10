/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:37:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 21:44:43 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	vector_create(float x, float y, float z)
{
	t_vec	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vec	vector_add(const t_vec a, const t_vec b)
{
	return (vector_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec	vector_subtract(const t_vec a, const t_vec b)
{
	return (vector_create(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec	vector_multiply(const t_vec a, float scalar)
{
	return (vector_create(a.x * scalar, a.y * scalar, a.z * scalar));
}

float	vector_length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
