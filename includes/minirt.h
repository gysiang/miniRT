/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/01 12:06:02 by bhowe            ###   ########.fr       */
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
# include <stdbool.h>
# include "vector.h"

# define IMG_WIDTH 800
# define IMG_HEIGHT 600
# define PI 3.14159265358979323846
# define MAX_OBJ 10

// Struct for RGB values
typedef struct s_rgb
{
	int r;
	int g;
	int b;
}	t_rgb;

// Struct for camera data
// vector is the orientation vector (given)
typedef struct s_camera
{
	t_coords 	position;
	t_coords 	vector;
	int			fov;
	float		aspect_ratio;
	int			vertical_fov;
	float		scale;
	t_coords	up_vector;
	t_coords	right_vector;
	float		half_width;
	float		half_height;
}	t_camera;

// Struct for light data
typedef struct s_light
{
	t_coords position;
	float	brightness;
	//t_rgb	rgb;
}	t_light;

typedef struct s_ray
{
	t_coords origin;
	t_coords vector;
} t_ray;

// Struct for sphere data
typedef struct s_sphere
{
	t_coords position;
	float	diameter;
	float	radius;
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
	// There can be multiple planes, cylinder, spheres so there needs to have an array to store it
	t_sphere	spheres[MAX_OBJ];
	int			sphere_count;
	t_plane		planes[MAX_OBJ];
	int			plane_count;
	t_cylinder	cylinders[MAX_OBJ];
	int			cylinder_count;
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

// ray logic
t_ray	make_ray(t_img *data, int x, int y);
bool	hit_sphere(t_ray *ray, t_sphere *sphere, float *t);
int		trace_ray(t_ray *ray, t_img *data);

// render
void	render_ambient(t_prog *mlx, float s, t_rgb *amb);
void	render_image(t_prog *prog, t_img *data);
void draw_sphere_projection(t_prog *prog, t_sphere *sphere);

// render - rgb
int		rgb_get(t_rgb rgb);
t_rgb	rgb_mul(t_rgb rgb, float ratio);
t_rgb	rgb_mix(t_rgb x, t_rgb y);
t_rgb	rgb_lerp(t_rgb x, t_rgb y, float frac);

#endif
