/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:17:49 by obibby            #+#    #+#             */
/*   Updated: 2023/02/22 19:56:09 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/car.h"

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
			colour |= 1UL << 24;
			colour |= 1UL << 25;
			colour |= 1UL << 26;
			colour |= 1UL << 27;
			colour |= 1UL << 28;
			colour |= 1UL << 29;
			colour |= 1UL << 30;
			colour |= 1UL << 31;
			put_pixel(dest, x, y, colour);
		}
	}
}

// encodes an int with trgb colour values.
int	colourshift(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
