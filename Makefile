# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:08:09 by cudoh             #+#    #+#              #
#    Updated: 2023/02/21 22:07:27 by cudoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRCS:= $(shell ls *.c | grep -v lst | xargs)

SRCS:= ./src/WavLib.c ./src/TimeLib.c ./src/main.c ./src/FftLib.c \
	   ./src/PlaySong.c
OBJS:= $(SRCS:.c=.o)


NAME = wavtest

CC = cc
#CFLAGS = -Werror -Wall -Wextra -g
CFLAGS = -g 
LIBFLAGS_STATIC = -L/usr/lib/x86_64-linux-gnu/  -lfftw3 -lm -lpthread -lrt -lSDL2
INCLUDES = -I./inc -I/usr/include/SDL2/ -DDEBUG

NAME : all
all : $(NAME)
$(NAME) : $(OBJS) $(USR_LIB)
	@echo "\033[1;33mCompiling Executables: $(NAME) \033[0m"
	$(CC) $^ $(CFLAGS) $(LIBFLAGS_STATIC) $(INCLUDES) -o $@
	@echo; echo "\033[1;32mCompilation Successful. \033[0m"
	@echo; echo

	


# obj files output
%.o : %.c
	@echo
	@echo "\033[1;33mCompiling OBJ files \033[0m"
	$(CC) -c $^ $(CFLAGS) $(LIBFLAGS_STATIC) $(INCLUDES) -o $@
	@echo



# remove all object files
fclean:
	rm -rf *.o

# remove final target files
clean: fclean
	rm -rf $(NAME)

# recompile everything
re: clean all

.PHONY : all fclean clean re 
