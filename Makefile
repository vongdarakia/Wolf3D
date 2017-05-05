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

NAME		=	wolf3d
LIB			=	lib/libft/libft.a
PFLIB		=	lib/ft_printf/ft_printf.a
MLX			=	lib/minilibx/libmlx.a

CC			=	gcc
INC			=	-I includes
LIBINC		=	-I lib/libft/includes
PFINC		=	-I lib/ft_printf/includes
CFLAGS		=	#-I includes/ #-Wall -Wextra -Werror #-fsanitize=address $(IDIR)
LFLAGS		=	lib/ft_printf/ft_printf.a
LFLAGS		+=	lib/libft/libft.a
MLFLAGS		=	-I lib/minilibx/ -L lib/minilibx/ -lmlx -framework OpenGL -framework AppKit
SRCS		= 	main.c \
				draw.c \
				read.c \
				ray.c \
				key_handler.c \
				get_next_line.c \
				structs.c \
				helper.c

ODIR		=	build
OBJS		=	$(addprefix build/, $(SRCS:.c=.o)) 

.PHONY: all clean fclean re

all: $(NAME)

build:
	@mkdir build/

$(NAME): $(OBJS) $(LIB) $(PFLIB) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(MLFLAGS) -o $(NAME)

build/%.o: srcs/%.c | build
	$(CC) $(INC) $(LIBINC) -I lib/minilibx/ $(CFLAGS) -c $< -o $@

$(LIB):
	make re -C lib/libft/

$(PFLIB):
	make re -C lib/ft_printf/

$(MLX):
	make re -C lib/minilibx/

clean:
	rm -f $(ODIR)/*.o 
	rm -rf build

fclean: clean
	rm -f $(NAME)
	make fclean -C lib/ft_printf/
	make fclean -C lib/libft/
	make clean -C lib/minilibx/

re: fclean all
