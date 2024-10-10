/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:12:09 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/09 11:18:40 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <math.h>
#include <stdio.h>

// Struct for 3D coordinates (x, y, z)
typedef struct s_vec
{
	float x;
	float y;
	float z;
}	t_vec;

typedef struct {
	float m[4][4];
} matrix4x4;

typedef struct s_matrix
{
	t_vec	m[3];
}	t_matrix;

static const t_vec UP_VECTOR = {0.0, 1.0, 0.0};
static const t_vec RIGHT_VECTOR = {1.0, 0.0, 0.0};

t_vec	vector_Add(const t_vec a, const t_vec b);
t_vec	vector_Subtract(const t_vec a, const t_vec b);
t_vec	vector_Multiply(const t_vec a, float scalar);
float	vector_Length(t_vec v);
t_vec	vector_Normalize(t_vec v);
t_vec	vector_CrossProduct(const t_vec a, const t_vec b);
float	vector_DotProduct(const t_vec a, const t_vec b);
t_vec	vector_create(float x, float y, float z);

// matrix.c
t_vec matrix_multiply_vector(matrix4x4 *mat, t_vec *v);
matrix4x4 create_camera_to_world_matrix(t_vec position, t_vec forward, t_vec up);

#endif
