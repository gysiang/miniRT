/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/17 15:20:05 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef enum type
{
	SP,
	PL,
	CY
}	t_type;

typedef struct s_sp
{
	float	xyz[3];
	float	dia;
	int		rgb[3];
}	t_sp;

typedef struct s_pl
{
	float	xyz[3];
	float	vec[3];
	int		rgb[3];
}	t_pl;

typedef struct s_cy
{
	float	xyz[3];
	float	vec[3];
	float	dia;
	float	height;
	int		rgb[3];
}	t_cy;

union	u_type
{
	t_sp	sp;
	t_pl	pl;
	t_cy	cy;
};

typedef struct s_elem
{
	union u_type	type_data;
	t_type			type_lex;
}	t_elem;

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
