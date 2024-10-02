/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:14:34 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/02 17:24:52 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *  Upates the camera position based on wasd
 */

void move_camera(t_vec *pos, t_vec *direction, float speed)
{
	pos->x += direction->x * speed;
	pos->y += direction->y * speed;
	pos->z += direction->z * speed;
}
