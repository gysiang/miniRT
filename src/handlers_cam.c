/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:14:34 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/09 23:03:02 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_camera(t_vec *pos, float scalar, int type)
{
	if (type == LEFTRIGHT)
		pos->x += scalar;
	else if (type == UPDOWN)
		pos->y += scalar;
	else if (type == FORWARDBACK)
		pos->z += scalar;
}

void	rotate_camera(t_camera *camera)
{
	t_vec new_direction;

	new_direction.x = cos(camera->pitch) * sin(camera->yaw);
	new_direction.y = sin(camera->pitch);
	new_direction.z = cos(camera->pitch) * cos(camera->yaw);
	new_direction = vector_Normalize(new_direction);
	camera->vector = new_direction;
}
