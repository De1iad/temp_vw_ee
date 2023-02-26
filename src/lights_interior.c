/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_interior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:37:58 by obibby            #+#    #+#             */
/*   Updated: 2023/02/25 23:48:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/car.h"

void	interior_front(t_car *car)
{
	int		x;
	int		y;
	double	alpha;

	y = 55;
	if (!EasterEggLightsEE.AmbientLights)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.AmbientLightsPWM * 0.0008;
	while (++y < 95)
	{
		x = 153;
		while (++x < 300)
			put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 51 * alpha, 0 * alpha, 102 * alpha));
	}
}

void	interior(t_car *car)
{
	interior_front(car);
}
