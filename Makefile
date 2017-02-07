# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avongdar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/12 02:38:02 by avongdar          #+#    #+#              #
#    Updated: 2017/01/23 16:41:23 by avongdar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB			=	libft/libft.a
MLX			=	minilibx/libmlx.a
NAME		=	wolf3d

IDIR		=	includes
CC			=	gcc
CFLAGS		=	-I includes/ #-Wall -Wextra -Werror #-fsanitize=address -I $(IDIR)
LFLAGS		=	-I libft/includes -L libft/ -lft
MLFLAGS		=	-I minilibx/ -L minilibx/ -lmlx -framework OpenGL -framework AppKit
SRCS		= 	main.c \
				draw.c

ODIR		=	build
OBJS		=	$(addprefix build/, $(SRCS:.c=.o)) 

.PHONY: all clean fclean re

all: $(NAME)

build:
	@mkdir build/

$(NAME): $(OBJS) $(LIB) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(MLFLAGS) -o $(NAME)

build/%.o: srcs/%.c | build
	$(CC) -I includes/ -I libft/includes -I minilibx/ $(CFLAGS) -c $< -o $@

$(LIB):
	make re -C libft/

$(MLX):
	make re -C minilibx/

clean:
	rm -f $(ODIR)/*.o 
	rm -rf build

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/
	make clean -C minilibx/

re: fclean all
