/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:19:44 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/09 17:18:20 by gyong-si         ###   ########.fr       */
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
	render_image(prog, data);
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
