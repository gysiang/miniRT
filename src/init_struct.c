/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:19:44 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/09 22:45:05 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_program(t_data *data)
{
	t_prog *prog;

	prog = &data->program;
	prog->mlx_ptr = NULL;
	prog->mlx_ptr = mlx_init();
	prog->win_ptr = mlx_new_window(prog->mlx_ptr, IMG_WIDTH, IMG_HEIGHT, "miniRT");
	prog->image = new_img(prog);
	mlx_hook(prog->win_ptr, 17,  0, handle_exit, data);
	mlx_hook(prog->win_ptr, 2, 1L<<0, handle_keypress, data);
	mlx_mouse_hook(data->program.win_ptr, handle_mouse_click, prog);
	render_image(data);
	mlx_loop(prog->mlx_ptr);
}

t_data	init_data(void)
{
	t_data	data;

	data.amb_count = 0;
	data.cam_count = 0;
	data.light_count = 0;
	data.prim_count = 0;
	data.error_flag = 0;
	return (data);
}
