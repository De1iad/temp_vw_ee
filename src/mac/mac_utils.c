/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mac_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:02:25 by obibby            #+#    #+#             */
/*   Updated: 2023/02/26 03:30:16 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/car.h"

// puts a pixel to an image.
void	put_pixel(t_image *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bpp / 8));
	*(int*)dst = colour;
}

// finds colour of individual pixel in car image.
int	get_pixel_colour(t_image *img, int x, int y)
{
	int	colour;

	colour = *(int *)(img->addr + y % 782 * img->line_size
			+ x % 960 * (img->bpp / 8));                                                                                                                                                                                                                                                                                                                                           
	return (colour);
}

// puts car image to an image, setting alpha to zero.
void	put_image(t_image *dest, t_image *src)
{
	int	x;
	int	y;
	int	colour;

	x = -1;
	while (++x < 960)
	{
		y = -1;
		while (++y < 782)
		{
			colour = get_pixel_colour(src, x, y);
			put_pixel(dest, x, y, colour);
		}
	}
}

// encodes an int with trgb colour values.
int	colourshift(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	*make_image(void *mlx)
{
	t_image istruct;
	int x;
	int y;
	int colour;

	istruct.img = mlx_new_image(mlx, 960, 782);
	istruct.addr = mlx_get_data_addr(istruct.img, &istruct.bpp, &istruct.line_size, &istruct.endian);
	colour = colourshift(255, 0, 0, 0);
	x = -1;
	while (++x < 960)
	{
		y = -1;
		while (++y < 782)
			put_pixel(&istruct, x, y, colour);
	}
	return (istruct.img);
}

// frees all allocated memory and exits.
int ft_free(t_car *car)
{
	mlx_destroy_image(car->mlx, car->image.img);
	mlx_destroy_image(car->mlx, car->alpha_image.img);
	//mlx_destroy_display(car->mlx);
	exit(0);
}
