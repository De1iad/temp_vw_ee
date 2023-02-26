/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_brake.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:37:13 by obibby            #+#    #+#             */
/*   Updated: 2023/02/26 03:16:00 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/car.h"

void	brake_lights_side(t_car *car)
{
	int		x;
	int		y;
	int		y_base;
	int		y_length;
	double	alpha;

	y_length = 10;
	x = 466;
	y_base = 435;
	if (!EasterEggLightsEE.BrakeLights)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BrakeLightsPWM * 0.0008;
	while (++x < 516)
	{
		y = y_base - y_length;
		while (++y < y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
		y_length++;
	}
	y_length = 52;
	x = 90;
	y_base = 585;
	if (!EasterEggLightsEE.BrakeLights)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BrakeLightsPWM * 0.0008;
	while (++x < 133)
	{
		y = y_base - y_length;
		while (++y <  y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
		y_length--;
	}
}

void	brake_lights_top(t_car *car)
{
	int		x;
	int		y;
	int		x_length;
	double	alpha;

	x_length = 780;
	y = 675;
	if (!EasterEggLightsEE.BrakeLights)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BrakeLightsPWM * 0.0008;
	while (++y < 745)
	{
		x = 767;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
		x_length++;
	}
	x_length = 13;
	y = 675;
	while (++y < 745)
	{
		x = 708 - x_length;
		while (++x < 708)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
		x_length++;
	}
}

void	brake_lights_rear(t_car *car)
{
	int		x;
	int		y;
	int		x_length;
	double	alpha;

	x_length = 840;
	y = 130;
	if (!EasterEggLightsEE.BrakeLights)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BrakeLightsPWM * 0.0008;
	while (++y < 250)
	{
		x = 805;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
		x_length++;
	}
	x_length = 35;
	y = 130;
	while (++y < 250)
	{
		x = 658 - x_length;
		while (++x < 658)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
		x_length++;
	}
}

void	brake_lights(t_car *car)
{
	brake_lights_rear(car);
	brake_lights_top(car);
	brake_lights_side(car);
}
