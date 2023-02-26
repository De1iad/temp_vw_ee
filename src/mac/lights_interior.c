/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_interior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:37:58 by obibby            #+#    #+#             */
/*   Updated: 2023/02/26 04:09:59 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/car.h"

void	interior_front(t_car *car)
{
	int		x;
	int		y;
	double	alpha;

	y = 55;
	if (!EasterEggLightsEE.AmbientLights)
		alpha = 255;
	else
		alpha = 255 - EasterEggLightsEE.AmbientLightsPWM * 255 * 0.001;
	while (++y < 95)
	{
		x = 153;
		while (++x < 300)
			put_pixel(&car->alpha_image, x, y, colourshift(alpha, 51, 0, 102));
	}
}

void	interior(t_car *car)
{
	interior_front(car);
}
