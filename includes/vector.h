/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:12:09 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/28 19:05:47 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <math.h>
#include <stdio.h>

// Struct for 3D coordinates (x, y, z)
typedef struct s_coords
{
	float x;
	float y;
	float z;
}	t_coords;

static const t_coords UP_VECTOR = {0.0, 1.0, 0.0};
static const t_coords RIGHT_VECTOR = {1.0, 0.0, 0.0};

t_coords vector_Add(const t_coords *a, const t_coords *b);
t_coords vector_Subtract(const t_coords *a, const t_coords *b);
t_coords vector_Normalize(const t_coords *v);
t_coords vector_CrossProduct(const t_coords *a, const t_coords *b);
float	vector_DotProduct(const t_coords *a, const t_coords *b);


#endif
