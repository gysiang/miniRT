/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 16:33:31 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../library/libft/includes/libft.h"
# include "../library/mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include "vector.h"

# define IMG_WIDTH 800
# define IMG_HEIGHT 600
# define PI 3.14159265358979323846
# define EPSILON 1e-6

# define MV_SPEED 5
# define ROT_SPEED 0.05

enum e_move
{
	LEFTRIGHT,
	UPDOWN,
	FORWARDBACK
};

// Struct for RGB values
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// Ray data related
typedef struct s_ray
{
	t_vec	origin;
	t_vec	vector;
	t_vec	hitpoint;
	t_vec	normal;
	bool	norm_flip;
}	t_ray;

typedef struct s_rayparams
{
	float	t;
	float	min_dist;
	t_vec	t_hitpoint;
	t_vec	t_normal;
	int		color_fin;
	// Components to calculate final color
	t_rgb	amb_fin;
	t_rgb	diffuse_fin;
	// Derivatives to find above components
	t_rgb	amb_def;
	t_rgb	prim_col;
	float	light_intensity;
	bool	t_norm_flip;
	t_ray	shadow;
	float	dl;
}	t_rayparams;

// Struct for camera data
// vector is the orientation vector (given)
typedef struct s_camera
{
	t_vec	position;
	t_vec	vector;
	int		fov;
	float	aspect_ratio;
	int		vertical_fov;
	float	scale;
	t_vec	up_vector;
	float	half_width;
	float	half_height;
	float	yaw;
	float	pitch;
}	t_camera;

// Struct for light data
typedef struct s_light
{
	t_vec	position;
	float	brightness;
	t_rgb	rgb;
}	t_light;

// Helper struct for solving quadratic equations
typedef struct s_qdtc
{
	float	discrim;
	float	discrim_sqrt;
	float	a;
	float	b;
	float	c;
	float	t1;
	float	t2;
}	t_qdtc;

// Struct for sphere data
typedef struct s_sphere
{
	float	radius;
}	t_sphere;

// Struct for cylinder data
typedef struct t_cylicone
{
	float	radius;
	float	height;
}	t_cylicone;

// Helper struct for cylinder calculations
typedef struct s_cyn_helper
{
	t_ray	*ray;
	t_vec	oc;
	t_vec	axis_proj;
	t_vec	perp;
	t_vec	oc_perp;
	bool	hit_body;
	bool	hit_cap;
	float	y_hit;
	float	y_min;
	float	y_max;
	bool	top_cap;
}	t_cyn_helper;

typedef enum type
{
	SP,
	PL,
	CY,
	CN
}	t_type;

union	u_type
{
	t_sphere	sp;
	t_cylicone	cyn;
};

typedef struct s_prim
{
	union u_type	p_data;
	t_type			p_type;
	t_vec			position;
	t_vec			vector;
	t_rgb			rgb;
}	t_prim;

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

// Main data struct
typedef struct s_data
{
	t_prog		program;
	float		amb_light;	// Ambient light ratio
	t_rgb		amb_rgb;	// Ambient light color
	int			amb_count;
	t_camera	camera;		// Camera data
	int			cam_count;
	t_light		light;		// Light data
	int			light_count;
	//An array that contains all ray hittable primitives
	t_prim		*prims;
	int			prim_count;
	int			error_flag;
}	t_data;

// free
void	free_array(char **array);
void	cleanup(t_data *data);

// init_struct
void	init_program(t_data *data);
t_data	init_data(void);

// checks
int		check_FileContents(t_data *data, int fd);
int		not_element(char **s);
int		check_capital_elements(t_data *data);
int		check_ambient(t_data *data, char **s);
int		check_cam(t_data *data, char **s);
int		check_lights(t_data *data, char **s);

// check_prims
int		check_spheres(t_data *data, char **s);
int		check_planes(t_data *data, char **s);
int		check_cylinders(t_data *data, char **s);
int		check_cones(t_data *data, char **s);

// check_util1
int		check_FileType(const char *filename);
int		open_file(int *fd, const char *filename);
int		ft_error(char *msg);
int		check_NumOfInputs(char **s, int n);
int		check_RGB(char *s);
int		check_XYZ(char *s);

// check_util2
int		check_Vector(char *s);
int		check_FOV(char *s);
int		check_Ratio(char *s);

// save
int		save_FileContents(t_data *data, int fd);
int		save_RGB(t_rgb *array, char *s);
int		save_Vector(t_vec *array, char *s);

// save_c_elems
int		save_AmbientLight(t_data *data, char **s);
int		save_Camera(t_data *data, char **s);
int		save_Light(t_data *data, char **s);

// save_prims
int		save_sphere(t_data *data, char **s);
int		save_plane(t_data *data, char **s);
int		save_cylicone(t_data *data, char **s);

// handlers
int		handle_exit(t_data *data);
int 	handle_keypress(KeySym keysym, t_data *data);
int		handle_mouse_click(int button, int x, int y);

// handlers - camera movement;
void	rotate_camera(t_camera *camera);
void	move_camera(t_vec *pos, float scalar, int type);

// image
void	set_img_pixel(t_image *img, int x, int y, int color);
t_image	*del_img(t_prog *mlx, t_image *img);
t_image	*new_img(t_prog *mlx);

// ray - logic
t_ray	make_ray(t_data *data, int x, int y);
int		trace_ray(t_ray *ray, t_data *data);

// ray - hits
bool	hit_prim(t_ray *ray, t_prim prim, t_rayparams *rp);
bool	hit_sphere(t_ray *ray, t_prim *prim, float *t);
bool	hit_plane(t_ray *ray, t_prim *prim, float *t);
bool	hit_cylinder(t_ray *ray, t_prim *prim, float *t);
bool	hit_cone(t_ray *ray, t_prim *prim, float *t);

// ray - hits_utils
t_vec	get_hitpoint(t_vec origin, t_ray *ray, float t);
bool	do_quadratic(t_qdtc *qd, float *t);

// ray - lighting
void	calc_color(t_data *data, t_rayparams *rp);
float	calculate_lighting(t_rayparams *rp, t_light *light);
t_ray	create_shadow(t_data *data, t_rayparams *rp);
bool	in_shadow(t_data *data, t_rayparams *rp);

// render
void	render_image(t_data *data);
void	re_render_image(t_data *data);

// render - rgb
int		rgb_get(t_rgb rgb);
t_rgb	rgb_add(t_rgb x, t_rgb y);
t_rgb	rgb_mul(t_rgb rgb, float ratio);
t_rgb	rgb_mix(t_rgb x, t_rgb y);
t_rgb	rgb_lerp(t_rgb x, t_rgb y, float frac);

#endif
