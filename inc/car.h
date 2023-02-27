/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:03:35 by obibby            #+#    #+#             */
/*   Updated: 2023/02/26 21:35:15 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAR_H
# define CAR_H

# include "../minilibx_linux/mlx.h"
# include "EasterEgg.h"
# include "WavLib.h"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

#ifdef __APPLE__
	#define KEY_ESC 53
	#define KEY_UP 126
	#define	KEY_LEFT 123
	#define KEY_RIGHT 124
	#define	KEY_DOWN 125
	#define	KEY_F 3
	#define	KEY_Q 113
	#define	KEY_W 119
	#define	KEY_E 101
	#define KEY_R 15
	#define	KEY_T 116
#else
	#define	KEY_ESC 65307
	#define KEY_UP 65362
	#define KEY_LEFT 65361
	#define	KEY_RIGHT 65363
	#define	KEY_DOWN 65364
	#define	KEY_F 102
	#define	KEY_Q 113
	#define	KEY_W 119
	#define	KEY_E 101
	#define	KEY_R 114
	#define	KEY_T 116
#endif

extern inputsEE EasterEggLightsEE;

typedef struct s_wav t_wav;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
} t_image;

typedef struct s_car
{
	void	*mlx; // the mlx pointer.
	void	*window; // pointer to the active window.
	t_image	xpm; // xpm image of the car.
	t_image	image; // image used to buffer before pushing to window.
	t_image	alpha_image;
	time_t	current_time;
	time_t	previous_time;
	time_t	loop_time;
	t_wav	wav;
	double max_amp[22050];
} t_car;


// image.c
void	put_pixel(t_image *img, int x, int y, int colour);
int		get_pixel_colour(t_image *img, int x, int y);
void	put_image(t_image *dest, t_image *src);
int		colourshift(int t, int r, int g, int b);

// utils.c
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

void	main_lights(t_car *car);
void	fog_lights(t_car *car);
void	indicators(t_car *car);
void	interior(t_car *car);
void	parking_lights(t_car *car);
void	brake_lights(t_car *car);
void	license_plate(t_car *car);

void	*make_image(void *mlx);
int 	ft_free(t_car *car);


#endif
