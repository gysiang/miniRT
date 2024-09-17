/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/17 21:00:35 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

/**
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
	int cylinder_vector[3];
	float	cylinder_dia;
	double	cylinder_height;
	int	cylinder_rgb[3];
}	t_img;
**/

// Struct for RGB values
typedef struct s_rgb
{
	int r;
	int g;
	int b;
}	t_rgb;

// Struct for 3D coordinates (x, y, z)
typedef struct s_coords
{
	int x;
	int y;
	int z;
}	t_coords;

// Struct for camera data
typedef struct s_camera
{
	t_coords position;
	t_coords vector;
	int		fov;
}	t_camera;

// Struct for light data
typedef struct s_light
{
	t_coords position;
	float	brightness;
	//t_rgb	rgb;
}	t_light;

// Struct for sphere data
typedef struct s_sphere
{
	t_coords position;
	float	diameter;
	t_rgb	rgb;
}	t_sphere;

// Struct for plane data
typedef struct s_plane
{
	t_coords position;
	t_coords vector;
	t_rgb	rgb;
}	t_plane;

// Struct for cylinder data
typedef struct s_cylinder
{
	t_coords position;
	t_coords vector;
	float	diameter;
	double	height;
	t_rgb	rgb;
}	t_cylinder;

// Main image struct
typedef struct s_img
{
	int			amb_light;	// Ambient light ratio
	t_rgb		amb_rgb;	// Ambient light color
	t_camera	camera;		// Camera data
	t_light		light;		// Light data
	t_sphere	sphere;		// Sphere data
	t_plane		plane;		// Plane data
	t_cylinder	cylinder;	// Cylinder data
}	t_img;


void	free_array(char **array);
// init_struct
void	init_img_data(t_img *data);

// checks
int	checkfiletype(const char *filename);
int	check_Ambient(t_img *data, char *line);
int	check_Cam(t_img *data, char *line);
int	check_Light(t_img *data, char *line);
int	check_Sp(t_img *data, char *line);
int	check_Cylinder(t_img *data, char *line);
char *normalize_whitespace(const char *str);

#endif
