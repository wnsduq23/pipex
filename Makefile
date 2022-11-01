# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 21:45:58 by junykim           #+#    #+#              #
#    Updated: 2022/11/01 23:02:37 by junykim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# variables
NAME 		= pipex

CC			= cc
CFLAG		= -Werror -Wextra -Wall
INC			= .
DEL			= rm -f
ARC			= ar -rcs
LIBFT		= libft

# srcs
# OBJ_DIR		= obj/
SRC_FILES	= pipex \
			  util \
			  free \
			  here_doc \
			  file \
			  main
SRCS		= $(addsuffix .c, $(SRC_FILES))
OBJS		= $(addsuffix .o, $(SRC_FILES))

SRC_B_FILES	= pipex \
			  util \
			  free \
			  here_doc \
			  main \
			  file
SRCS_B		= $(addsuffix _bonus.c, $(SRC_B_FILES))
OBJS_B		= $(addsuffix _bonus.o, $(SRC_B_FILES))

ifdef WITH_BONUS
	OBJ = $(OBJS_B)
else
	OBJ = $(OBJS)
endif

# rules
all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@mv $(LIBFT)/libft.a .
	$(ARC) $@ $(OBJ)
	$(CC) $(CFLAG) $(OBJ) libft.a -o $@
	@echo "==================pipex compiled finished=================="

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@ -I $(INC)

bonus :
	@make WITH_BONUS=1 all

clean :
	$(DEL) $(OBJS) $(OBJS_B)
	$(DEL) libft.a
	make clean -C $(LIBFT)
	@echo "=================pipex obj files have been deleted================="

fclean : clean
	$(DEL) $(NAME)
	$(DEL) $(LIBFT)/libft.a
	@ echo "=================pipex all files have been deleted================"

re :
	make fclean
	make all

.PHONY : all clean fclean re bonus
