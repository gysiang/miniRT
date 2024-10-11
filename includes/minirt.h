/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:21:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/11 23:39:18 by bhowe            ###   ########.fr       */
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

enum e_cy_part
{
	BODY,
	CAP
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

// helper struct to calculate final color.
// amb_fin & diffuse_fin contribute.
// below those two are the derivatives
typedef struct s_rayparams
{
	float	t;
	float	min_dist;
	t_vec	t_hitpoint;
	t_vec	t_normal;
	int		color_fin;
	t_rgb	amb_fin;
	t_rgb	diffuse_fin;
	t_rgb	color_temp;
	bool	first_light_calc;
	t_rgb	amb_def;
	t_rgb	prim_col;
	float	light_intensity;
	bool	t_norm_flip;
	t_ray	shadow;
	float	dl;
	int		prim_num;
}	t_rayparams;

// Struct for camera data
typedef struct s_camera
{
	t_vec	position;
	t_vec	vector;
	int		fov;
	float	aspect_ratio;
	int		vertical_fov;
	float	scale;
	t_vec	up_vector;
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
typedef struct s_cylinder
{
	float	radius;
	float	height;
}	t_cylinder;

// Helper struct for cylinder calculations
typedef struct s_cy_helper
{
	t_ray	*ray;
	t_vec	oc;
	t_vec	axis_proj;
	t_vec	perp;
	t_vec	oc_perp;
	bool	hit_body;
	bool	top_cap;
	bool	bot_cap;
	t_vec	cap_vec;
	float	y_hit;
	float	y_min;
	float	y_max;
}	t_cy_helper;

typedef enum type
{
	SP,
	PL,
	CY
}	t_type;

union	u_type
{
	t_sphere	sp;
	t_cylinder	cy;
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
	float		amb_light;
	t_rgb		amb_rgb;
	int			amb_count;
	t_camera	camera;
	int			cam_count;
	t_light		light;
	t_light		*light_arr;
	int			light_count;
	t_prim		*prims;
	int			prim_count;
}	t_data;

// free
void	free_array(char **array);
void	cleanup(t_data *data);

// init_struct
void	init_program(t_data *data);
t_data	init_data(void);

// checks
int		check_filecontents(t_data *data, int fd);
int		not_element(char **s);
int		check_capital_elements(t_data *data);

// check_elems
int		check_ambients(t_data *data, char **s);
int		check_cams(t_data *data, char **s);
int		check_spheres(t_data *data, char **s);
int		check_planes(t_data *data, char **s);
int		check_cylinders(t_data *data, char **s);

// manage_elems_light
int		check_capital_elements(t_data *data);
int		check_lights(t_data *data, char **s);
int		setup_elem_data(t_data *data);
int		save_light(t_data *data, char **s);

// check_util1
int		check_xyz(char *s);
int		check_vector(char *s);
int		check_rgb(char *s);
int		check_fov(char *s);
int		check_ratio(char *s);

// check_util2
int		check_filetype(const char *filename);
int		open_file(int *fd, const char *filename);
int		ft_error(char *msg);
int		check_numofinputs(char **s, int n);
int		comma_check(char *s);

// save
int		save_filecontents(t_data *data, int fd);
int		save_ambientlight(t_data *data, char **s);
int		save_camera(t_data *data, char **s);
int		save_sphere(t_data *data, char **s);

// save1
int		save_plane(t_data *data, char **s);
int		save_cylinder(t_data *data, char **s);
int		save_rgb(t_rgb *array, char *s);
int		save_vector(t_vec *array, char *s);

// handlers
int		handle_exit(t_data *data);
int		handle_cam_movement(t_data *data, KeySym keysym);
int		handle_cam_rotation(t_data *data, KeySym keysym);
int		handle_light_movement(t_data *data, KeySym keysym);

// handlers1
int		handle_keypress(KeySym keysym, t_data *data);
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
void	update_hit_params(t_ray *ray, t_rayparams *rp, t_prim *prim);

// ray - hits
t_vec	get_hitpoint(t_vec origin, t_ray *ray, float t);
bool	do_quadratic(t_qdtc *qd, float *t);
bool	hit_sphere(t_ray *ray, t_prim *prim, float *t);
bool	hit_plane(t_ray *ray, t_prim *prim, float *t);
bool	hit_prim(t_ray *ray, t_prim prim, t_rayparams *rp);

// ray - hits_cy
void	init_cy_helper(t_ray *ray, t_prim *prim, t_cy_helper *cyh);
bool	hit_cylinder(t_ray *ray, t_prim *prim, float *t);
void	check_cylinder_caps(t_cy_helper *cyh, t_prim *prim, float *t);
void	hit_cylinder_part(t_cy_helper *cyh, t_prim *prim, float *t, int part);
bool	hit_disc(t_cy_helper *cyh, t_prim *prim, float y_offset, float *t);

// ray - lighting
void	calc_color(t_data *data, t_rayparams *rp);
float	calculate_lighting(t_rayparams *rp, t_light *light);
bool	in_shadow(t_data *data, t_rayparams *rp, t_light *light);

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
