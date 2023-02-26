# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 20:17:58 by libacchu          #+#    #+#              #
#    Updated: 2023/02/26 03:15:09 by obibby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	car_demo
OBJ_DIR =	obj/
SRC_DIR =	src/
SRC		=	main.c EasterEgg.c utils.c WavLib.c transform.c FftLib.c PlaySong.c
INC		=	inc/car.h inc/EasterEgg.h
SYS		=	$(shell uname -s)
ifeq ($(SYS), Linux)
	SRC		+=	linux/linux_utils.c linux/lights_main.c linux/lights_fog.c linux/lights_indicator.c linux/lights_interior.c linux/lights_parking.c linux/lights_brake.c linux/lights_license.c
    LIBS    =	-Lminilibx_linux -lmlx -lXext -lX11 -lXrender -L/usr/lib/x86_64-linux-gnu/  -lfftw3 -lm -lpthread -lrt -lSDL2
	LIBMLX	=	./minilibx_linux/
else
	SRC		+=	mac/mac_utils.c mac/lights_main.c mac/lights_fog.c mac/lights_indicator.c mac/lights_interior.c mac/lights_parking.c mac/lights_brake.c mac/lights_license.c
	LIBS    =	-Lminilibx_mms -lmlx -framework OpenGL -framework AppKit -lfftw3 -lm -lpthread -lSDL2
	LIBMLX	=	./minilibx_mms/
	COPY	=	cp minilibx_mms/libmlx.dylib .
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
	@$(COPY)
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