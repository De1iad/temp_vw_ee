# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 20:17:58 by libacchu          #+#    #+#              #
#    Updated: 2023/02/25 23:40:45 by obibby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	car_demo
OBJ_DIR =	obj/
SRC_DIR =	src/
SRC		=	main.c EasterEgg.c image.c utils.c lights_main.c lights_fog.c lights_indicator.c lights_interior.c lights_parking.c lights_brake.c lights_license.c WavLib.c TimeLib.c transform.c FftLib.c PlaySong.c
INC		=	inc/car.h inc/EasterEgg.h
SYS		=	$(shell uname -s)
ifeq ($(SYS), Linux)
	SRC		+=	linux.c
    LIBS    =	-Lminilibx_linux -lmlx -lXext -lX11 -lXrender -L/usr/lib/x86_64-linux-gnu/  -lfftw3 -lm -lpthread -lrt -lSDL2
	LIBMLX	=	./minilibx_linux/
else
	SRC		+=	mac.c
	LIBS    =	-Lminilibx_linux -lmlx -framework OpenGL -framework AppKit
	LIBMLX	=	./minilibx_mms/
endif
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))
OBJ		=	$(SRCS:%.c=$(OBJ_DIR)%.o)
CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror
CFLAGS	=	-DDEBUG
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
DEFLT	=	\33[0m
RESET	=	\33[2K

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "$(RESET)\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME) : $(OBJ) $(INC)
	@printf "\n"
	@make -C $(LIBMLX)
	@printf "$(RESET)\r$(GREY)Compiling $(BLUE)$(NAME)$(DEFLT)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)$(DEFLT)\n"
	@make clean -C $(LIBMLX)
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)$(DEFLT)\n"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re