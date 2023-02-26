/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_parking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:34:56 by obibby            #+#    #+#             */
/*   Updated: 2023/02/26 04:14:25 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/car.h"

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
		alpha = 255;
		if (get_pixel_colour(&car->alpha_image, 330, 153) != colourshift(alpha, 255, 165, 0))
			return ;
	}
	else
		alpha = 255 - EasterEggLightsEE.ParkingLightRightPWM * 255 * 0.001;
	while (++x < 485)
	{
		y = y_base - y_length;
		while (++y < y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(alpha, 255, 165, 0));
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
		alpha = 255;
		if (get_pixel_colour(&car->alpha_image, 330, 153) != colourshift(alpha, 255, 165, 0))
			return ;
	}
	else
		alpha = 255 - EasterEggLightsEE.ParkingLightLeftPWM * 255 * 0.001;
	while (++x < 128)
	{
		y = y_base - y_length;
		while (++y <  y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(alpha, 255, 165, 0));
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
		alpha = 255;
		if (get_pixel_colour(&car->alpha_image, 326, 176) != colourshift(alpha, 255, 165, 0))
			return ;
	}
	else
		alpha = 255 - EasterEggLightsEE.ParkingLightRightPWM * 255 * 0.001;
	i = 0;
	while (++y < 190)
	{
		x = 325 - i;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(alpha, 255, 165, 0));
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
		alpha = 255;
		if (get_pixel_colour(&car->alpha_image, 123, 176) != colourshift(alpha, 255, 165, 0))
			return ;
	}
	else
		alpha = 255 - EasterEggLightsEE.ParkingLightLeftPWM * 255 * 0.001;
	i = 0;
	while (++y < 190)
	{
		x = 122 - i;
		while (++x < x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(alpha, 255, 165, 0));
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
