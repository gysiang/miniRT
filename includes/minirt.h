/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/02 16:57:33 by bhowe            ###   ########.fr       */
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
	t_vec 	position;
	t_vec 	vector;
	int			fov;
	float		aspect_ratio;
	int			vertical_fov;
	float		scale;
	t_vec	up_vector;
	t_vec	right_vector;
	float		half_width;
	float		half_height;
}	t_camera;

// Struct for light data
typedef struct s_light
{
	t_vec position;
	float	brightness;
	t_rgb	rgb;
}	t_light;

// Ray data related
typedef struct s_ray
{
	t_vec origin;
	t_vec vector;
} t_ray;

typedef struct s_rayparams
{
	float	t;
	float	min_dist;
	t_rgb	amb;
	t_rgb	diffuse;
	t_rgb	prim_col;
	t_vec	prim_pos;
	t_vec	normal;
	t_vec	hitpoint;
	float	light_intensity;
} t_rayparams;

// Struct for sphere data
typedef struct s_sphere
{
	t_vec	position;
	float		diameter;
	float		radius;
	t_rgb		rgb;
}	t_sphere;

// Struct for plane data
typedef struct s_plane
{
	t_vec	position;
	t_vec	vector;
	t_rgb		rgb;
}	t_plane;

// Struct for cylinder data
typedef struct s_cylinder
{
	t_vec	position;
	t_vec	vector;
	float		diameter;
	double		height;
	t_rgb		rgb;
}	t_cylinder;

typedef enum type
{
	SP,
	PL,
	CY
}	t_type;

union	u_type
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

typedef struct	s_prim
{
	union u_type	p_data;
	t_type			p_type;
}	t_prim;

// Main image struct
typedef struct s_img
{
	char		*error_msg;
	float		amb_light;	// Ambient light ratio
	t_rgb		amb_rgb;	// Ambient light color
	t_camera	camera;		// Camera data
	t_light		light;		// Light data
	//An array that contains all ray hittable primitives
	t_prim		*prims;
	int			prim_count;
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
int	save_XYZ(t_vec *array, char *s);
int	save_Vector(t_vec *array, char *s);

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

// ray - hit
bool	hit_prim(t_ray *ray, t_prim prim, t_rayparams *rp);

// render
void	render_ambient(t_prog *mlx, float s, t_rgb *amb);
void	render_image(t_prog *prog, t_img *data);
void draw_sphere_projection(t_prog *prog, t_sphere *sphere);

// render - rgb
int		rgb_get(t_rgb rgb);
t_rgb	rgb_add(t_rgb x, t_rgb y);
t_rgb	rgb_mul(t_rgb rgb, float ratio);
t_rgb	rgb_mix(t_rgb x, t_rgb y);
t_rgb	rgb_lerp(t_rgb x, t_rgb y, float frac);

#endif
