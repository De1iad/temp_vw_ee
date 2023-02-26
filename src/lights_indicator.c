/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_indicator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:30:08 by obibby            #+#    #+#             */
/*   Updated: 2023/02/26 00:30:52 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/car.h"

void	left_indicator_front(t_car *car)
{
	int		x;
	int		y;
	static time_t	last_time;
	static int	displace;
	double	alpha;

	if (!EasterEggLightsEE.BlinkLightLeft)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BlinkLightLeftPWM * 0.0008;
	x = 126 - displace;
	while (++x < 134 - displace)
	{
		y = 82;
		while (++y < 87)
		{
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
			if (displace > 0)
			 	put_pixel(&car->alpha_image, x + 8, y, 0);
			else
				put_pixel(&car->alpha_image, x - 24, y, 0);
		}
	}
	x = 110;
	while (++x < 120)
	{
		y = 125;
		while (++y < 140)
		{
			if (displace == 24)
				put_pixel(&car->alpha_image, x, y, 0);
			else
				put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		}
	}
	if (car->current_time - last_time > 300)
	{
		displace += 8;
		last_time = car->current_time;
	}
	if (displace > 24)
		displace = 0;
}

void	right_indicator_front(t_car *car)
{
	int		x;
	int		y;
	static time_t	last_time;
	static int	displace;
	double	alpha;

	if (!EasterEggLightsEE.BlinkLightRight)
	{
		alpha = 0;
		// if (get_pixel_colour(&car->alpha_image, 330, 153) == colourshift(255 * alpha, 255 * alpha, 255 * alpha, 255 * alpha))
		// 	return ;
	}
	else
		alpha = EasterEggLightsEE.BlinkLightRightPWM * 0.0008;
	x = 320 + displace;
	while (++x < 328 + displace)
	{
		y = 82;
		while (++y < 87)
		{
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
			if (displace > 0)
			 	put_pixel(&car->alpha_image, x - 8, y, 0);
			else
				put_pixel(&car->alpha_image, x + 24, y, 0);
		}
	}
	x = 335;
	while (++x < 345)
	{
		y = 125;
		while (++y < 140)
		{
			if (displace == 24)
				put_pixel(&car->alpha_image, x, y, 0);
			else
				put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		}
	}
	if (car->current_time - last_time > 300)
	{
		displace += 8;
		last_time = car->current_time;
	}
	if (displace > 24)
		displace = 0;
}

void	left_indicator_side(t_car *car)
{
	int		x;
	int		y;
	int		x_length;
	double	alpha;

	x_length = 11;
	y = 421;
	if (!EasterEggLightsEE.BlinkLightLeft)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BlinkLightLeftPWM * 0.0008;
	while (++y < 429)
	{
		x = 253 - x_length;
		while (++x < 253)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
	}
}

void	right_indicator_side(t_car *car)
{
	int		x;
	int		y;
	int		x_length;
	double	alpha;

	x_length = 11;
	y = 570;
	if (!EasterEggLightsEE.BlinkLightRight)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BlinkLightRightPWM * 0.0008;
	while (++y < 578)
	{
		x = 358 - x_length;
		while (++x < 358)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
	}
}

void	left_indicator_top(t_car *car)
{
	int		x;
	int		y;
	int		i;
	int		y_length;
	double	alpha;

	y_length = 15;
	x = 650;
	i = 529;
	if (!EasterEggLightsEE.BlinkLightLeft)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BlinkLightLeftPWM * 0.0008;
	while (++x < 659)
	{
		y = 522 - y_length;
		while (++y < i)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		y_length--;
		i--;
	}
}

void	right_indicator_top(t_car *car)
{
	int		x;
	int		y;
	int		i;
	int		y_length;
	double	alpha;

	y_length = 0;
	x = 816;
	i = 524;
	if (!EasterEggLightsEE.BlinkLightRight)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.BlinkLightRightPWM * 0.0008;
	while (++x < 825)
	{
		y = 517 - y_length;
		while (++y < i)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 236 * alpha, 3 * alpha));
		y_length++;
		i++;
	}
}

void	left_indicator(t_car *car)
{
	left_indicator_side(car);
	left_indicator_top(car);
	left_indicator_front(car);
	// left_indicator_rear(car);
}

void	right_indicator(t_car *car)
{
	right_indicator_side(car);
	right_indicator_top(car);
	right_indicator_front(car);
}

void	indicators(t_car *car)
{
	right_indicator(car);
	left_indicator(car);
}
