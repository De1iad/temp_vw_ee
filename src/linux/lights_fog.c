/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_fog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:28:01 by obibby            #+#    #+#             */
/*   Updated: 2023/02/26 03:16:04 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/car.h"

void	fog_lights_side_right(t_car *car)
{
	int		x;
	int		y;
	int		y_base;
	int		y_length;
	double	alpha;

	y_length = 0;
	x = 470;
	y_base = 622;
	if (!EasterEggLightsEE.FogLights)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 330, 153) != colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.FogLightsPWM * 0.0008;
	while (++x < 500)
	{
		y = y_base - y_length;
		while (++y < y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		y_length++;
	}
}

void	fog_lights_side_left(t_car *car)
{
	int		x;
	int		y;
	int		y_base;
	int		y_length;
	double	alpha;

	y_length = 30;
	x = 98;
	y_base = 473;
	if (!EasterEggLightsEE.FogLights)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 330, 153) != colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.FogLightsPWM * 0.0008;
	while (++x < 128)
	{
		y = y_base - y_length;
		while (++y <  y_base + y_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		y_length--;
	}
}

void	fog_lights_front_right(t_car *car)
{
	int	x;
	int	x_base;
	int	y;
	int	x_length;
	double	alpha;

	x_base = 330;
	x_length = 1;
	y = 152;
	if (!EasterEggLightsEE.FogLights)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 330, 153) != colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.FogLightsPWM * 0.0008;
	while (++y < 212)
	{
		x = x_base - x_length;
		while (++x < x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		if (y < 162)
		{
			if (y % 2)
				x_length++;
		}
		else if (y >= 202)
		{
			if (y % 2)
				x_length--;
		}
		else if (y > 172 && y < 182)
			x_length += 2;
		else if (y >= 192)
			x_length--;
		else if (y >= 182)
			x_length -= 2;
		else
			x_length++;
	}
}

void	fog_lights_front_left(t_car *car)
{
	int	x;
	int	x_base;
	int	y;
	int	x_length;
	double	alpha;

	x_base = 126;
	x_length = 1;
	y = 152;
	if (!EasterEggLightsEE.FogLights)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 126, 153) != colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.FogLightsPWM * 0.0008;
	while (++y < 212)
	{
		x = x_base - x_length;
		while (++x < x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		if (y < 162)
		{
			if (y % 2)
				x_length++;
		}
		else if (y >= 202)
		{
			if (y % 2)
				x_length--;
		}
		else if (y > 172 && y < 182)
			x_length += 2;
		else if (y >= 192)
			x_length--;
		else if (y >= 182)
			x_length -= 2;
		else
			x_length++;
	}
}

void	fog_lights(t_car *car)
{
	fog_lights_front_right(car);
	fog_lights_front_left(car);
	fog_lights_side_right(car);
	fog_lights_side_left(car);
}
