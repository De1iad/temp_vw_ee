/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_license.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:09:44 by obibby            #+#    #+#             */
/*   Updated: 2023/02/22 19:57:46 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/car.h"

void	license_one(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 5;
	x_base = 700;
	y = 130;
	if (!EasterEggLightsEE.LicensePlateLight1)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, x_base, 131) == colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.LicensePlateLight1PWM * 0.0008;
	while (++y < 150)
	{
		x = x_base - x_length;
		while (++x < x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		x_length++;
	}
}

void	license_two(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 5;
	x_base = 760;
	y = 130;
	if (!EasterEggLightsEE.LicensePlateLight2)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, x_base, 131) == colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.LicensePlateLight2PWM * 0.0008;
	while (++y < 150)
	{
		x = x_base - x_length;
		while (++x < x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		x_length++;
	}
}

void	license_three(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 5;
	x_base = 720;
	y = 130;
	if (!EasterEggLightsEE.LicensePlateLight3)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, x_base, 131) == colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.LicensePlateLight3PWM * 0.0008;
	while (++y < 150)
	{
		x = x_base - x_length;
		while (++x < x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		x_length++;
	}
}

void	license_four(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 5;
	x_base = 740;
	y = 130;
	if (!EasterEggLightsEE.LicensePlateLight4)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, x_base, 131) == colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.LicensePlateLight4PWM * 0.0008;
	while (++y < 150)
	{
		x = x_base - x_length;
		while (++x < x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		x_length++;
	}
}

void	license_five(t_car *car)
{
	int		x;
	int		y;
	int		x_base;
	int		x_length;
	double	alpha;

	x_length = 5;
	x_base = 400;
	y = 130;
	if (!EasterEggLightsEE.LicensePlateLight5)
	{
		alpha = 0;
		if (get_pixel_colour(&car->alpha_image, 400, 131) == colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
			return ;
	}
	else
		alpha = EasterEggLightsEE.LicensePlateLight5PWM * 0.0008;
	while (++y < 150)
	{
		x = x_base - x_length;
		while (++x < x_base + x_length)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha));
		x_length++;
	}
}

void	license_plate(t_car *car)
{
	license_one(car);
	license_two(car);
	license_three(car);
	license_four(car);
	license_five(car);
}
