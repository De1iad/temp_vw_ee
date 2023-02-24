/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:10:52 by obibby            #+#    #+#             */
/*   Updated: 2023/02/24 20:09:21 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/car.h"

void	top_right_main(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 5;
	x_base = 696;
	y = 410;
	if (!EasterEggLightsEE.FrontLights)
		alpha = 0;
	else
		alpha = 0.5;
	while (--y > 340)
	{
		x = x_base - x_length;
		while (++x < x_base + (x_length * 0.5))
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		x_length++;
	}
}

void	top_left_main(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 5;
	x_base = 780;
	y = 410;
	if (!EasterEggLightsEE.FrontLights)
		alpha = 0;
	else
		alpha = 0.5;
	while (--y > 340)
	{
		x = x_base - (x_length * 0.5);
		while (++x <  x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		x_length++;
	}
}

void	side_right_main(t_car *car)
{
	int		x;
	int		y;
	int		y_base;
	int		y_length;
	double	alpha;

	y_length = 0;
	x = 460;
	y_base = 605;
	if (!EasterEggLightsEE.FrontLights)
		alpha = 0;
	else
		alpha = 0.5;
	while (++x < 510)
	{
		y = y_base - y_length;
		while (++y < y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		y_length++;
	}
}

void	side_left_main(t_car *car)
{
	int		x;
	int		y;
	int		y_base;
	int		y_length;
	double	alpha;

	y_length = 50;
	x = 90;
	y_base = 457;
	if (!EasterEggLightsEE.FrontLights)
		alpha = 0;
	else
		alpha = 0.5;
	while (++x < 140)
	{
		y = y_base - y_length;
		while (++y <  y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		y_length--;
	}
}

// draw front right light to image.
void	front_right_main(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 25;
	y = 130;
	x_base = 310;
	if (!EasterEggLightsEE.FrontLights)
		alpha = 0;
	else
		alpha = 0.5;
	while (++y < 250)
	{
		x = x_base - (x_length * 0.5);
		while (++x <  x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		x_length++;
	}
}

// draw front left light to image.
void	front_left_main(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 25;
	x_base = 145;
	y = 130;
	if (!EasterEggLightsEE.FrontLights)
		alpha = 0;
	else
		alpha = 0.5;
	while (++y < 250)
	{
		x = x_base - x_length;
		while (++x < x_base + (x_length * 0.5))
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		x_length++;
	}
}

void	main_lights(t_car *car)
{
	front_left_main(car);
	front_right_main(car);
	side_left_main(car);
	side_right_main(car);
	top_left_main(car);
	top_right_main(car);
}
