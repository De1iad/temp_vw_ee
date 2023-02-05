# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:08:09 by cudoh             #+#    #+#              #
#    Updated: 2023/01/29 19:56:46 by cudoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRCS:= $(shell ls *.c | grep -v lst | xargs)

SRCS:= sound.c fft_sample.c
OBJS:= $(SRCS:.c=.o)


NAME = play

CC = cc
#CFLAGS = -Werror -Wall -Wextra -g
CFLAGS = -g 
LIBFLAGS_STATIC = -L/usr/lib/x86_64-linux-gnu/ -lSDL2 -lfftw3 -lm
INCLUDES = -I./ -I/usr/include/SDL2/

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
