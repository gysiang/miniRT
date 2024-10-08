/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:26:42 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/02 15:58:08 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_img_pixel(t_image *img, int x, int y, int color)
{
	*(unsigned int *)(img->ptr + (y * img->line_length \
		+ x * img->bits_per_pixel)) = color;
}

t_image	*del_img(t_prog *mlx, t_image *img)
{
	if (img && img->img)
	{
		mlx_destroy_image(mlx->mlx_ptr, img->img);
		free(img);
		img = NULL;
	}
	return (0);
}

t_image	*new_img(t_prog *mlx)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (0);
	img->img = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	if (!img->img)
		return (del_img(mlx, img));
	img->ptr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	img->bits_per_pixel /= 8;
	return (img);
}
