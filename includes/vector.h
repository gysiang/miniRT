/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:12:09 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/24 10:17:59 by gyong-si         ###   ########.fr       */
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

// struct for Camera
typedef struct s_camera
{
	t_coords origin;
	t_coords forward;
	t_coords right;
	t_coords up;
} t_camera;


#endif
