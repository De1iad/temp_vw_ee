/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_parking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:34:56 by obibby            #+#    #+#             */
/*   Updated: 2023/02/22 19:57:52 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/car.h"

void	parking_light_side_right(t_car *car)
{
	int		x;
	int		y;
	int		y_base;
	int		y_length;
	double	alpha;

	y_length = 3;
	x = 472;
	y_base = 622;
	if (!EasterEggLightsEE.ParkingLightRight)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 330, 153) != colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.ParkingLightRightPWM * 0.0008;
	while (++x < 485)
	{
		y = y_base - y_length;
		while (++y < y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha));
		y_length++;
	}
}

void	parking_light_side_left(t_car *car)
{
	int		x;
	int		y;
	int		y_base;
	int		y_length;
	double	alpha;

	y_length = 13;
	x = 117;
	y_base = 473;
	if (!EasterEggLightsEE.ParkingLightLeft)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 330, 153) != colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.ParkingLightLeftPWM * 0.0008;
	while (++x < 128)
	{
		y = y_base - y_length;
		while (++y <  y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha));
		y_length--;
	}
}

void	parking_light_front_right(t_car *car)
{
	int		x;
	int		y;
	int		i;
	int		x_length;
	double	alpha;

	x_length = 333;
	y = 175;
	if (!EasterEggLightsEE.ParkingLightRight)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 326, 176) != colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.ParkingLightRightPWM * 0.0008;
	i = 0;
	while (++y < 190)
	{
		x = 325 - i;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha));
		x_length++;
		i++;
	}
}

void	parking_light_front_left(t_car *car)
{
	int		x;
	int		y;
	int		i;
	int		x_length;
	double	alpha;

	x_length = 130;
	y = 175;
	if (!EasterEggLightsEE.ParkingLightLeft)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 123, 176) != colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.ParkingLightLeftPWM * 0.0008;
	i = 0;
	while (++y < 190)
	{
		x = 122 - i;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 165 * alpha, 0 * alpha));
		x_length++;
		i++;
	}
}

void	parking_lights(t_car *car)
{
	parking_light_front_left(car);
	parking_light_front_right(car);
	parking_light_side_left(car);
	parking_light_side_right(car);
}
