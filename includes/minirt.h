/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/17 10:41:38 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_img
{
	// ambient
	int	amb_light;
	int	amb_rgb[3];
	// camera
	int cam_xyz[3];
	int	cam_vector[3];
	int	cam_fov;
	// light
	int	light_xyz[3];
	float	light_brightness;
	// sphere
	int	sphere_xyz[3];
	float	sphere_dia;
	int	sphere_rgb[3];
	// plane
	int	plane_xyz[3];
	int	plane_vector[3];
	int	plane_rgb[3];
	// cylinder
	int	cylinder_xyz[3];
	float	cylinder_dia;
	double	cylinder_height;
	int	cylinder_rgb[3];
}	t_img;

int	checkfiletype(const char *filename);

#endif
