/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/24 10:16:40 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../library/libft/includes/libft.h"
# include "../library/mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "vector.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

// Struct for RGB values
typedef struct s_rgb
{
	int r;
	int g;
	int b;
}	t_rgb;

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
	char		*error_msg;
	float		amb_light;	// Ambient light ratio
	t_rgb		amb_rgb;	// Ambient light color
	t_camera	camera;		// Camera data
	t_light		light;		// Light data
	t_sphere	sphere;		// Sphere data
	t_plane		plane;		// Plane data
	t_cylinder	cylinder;	// Cylinder data
}	t_img;

// mlx image struct
typedef struct s_image
{
	void	*img;
	char	*ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

// to save program data like mlx
typedef struct s_prog
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	*image;
}	t_prog;

void	free_array(char **array);
void	cleanup(t_prog *prog);

// init_struct
void	init_img_data(t_img *data);
void	init_program(t_prog *prog, t_img *data);

// checks
int	check_FileContents(t_img *data, int fd);
int	check_Ambients(t_img *data, char **s);
int	check_Cams(t_img *data, char **s);
int	check_Lights(t_img *data, char **s);
int	check_Spheres(t_img *data, char **s);

// checks1
int	check_Planes(t_img *data, char **s);
int	check_Cylinders(t_img *data, char **s);

// check_util1
int	check_FileType(const char *filename);
int set_error_msg(t_img *data, char *msg);
int	check_NumOfInputs(char **s, int n);
int	check_RGB(char *s);
int	check_XYZ(char *s);

// check_util2
int	check_Vector(char *s);
int	check_FOV(char *s);
int	check_Ratio(char *s);

// save
int save_FileContents(t_img *data, int fd);
int	save_AmbientLight(t_img *data, char **s);
int	save_Camera(t_img *data, char **s);
int	save_Light(t_img *data, char **s);
int	save_Sphere(t_img *data, char **s);

// save1
int	save_Plane(t_img *data, char **s);
int	save_Cylinder(t_img *data, char **s);
int	save_RGB(t_rgb *array, char *s);
int	save_XYZ(t_coords *array, char *s);
int	save_Vector(t_coords *array, char *s);


// handlers
void	exit_program(t_prog *prog);
int		handle_exit(t_prog *prog);
int		handle_keypress(int keycode, t_prog *program);
int		handle_mouse_click(int button, int x, int y);

// utils
char *normalize_whitespace(const char *str);

// image
void	set_img_pixel(t_image *img, int x, int y, int color);
t_image	*del_img(t_prog *mlx, t_image *img);
t_image	*new_img(t_prog *mlx);

// render
void	render_ambient(t_prog *mlx, float s, t_rgb *amb);

#endif
