# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avongdar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/22 09:55:57 by avongdar          #+#    #+#              #
#    Updated: 2017/01/12 02:09:53 by avongdar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_printf.a

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

FT_PRINTF		=	ft_printf ft_set_env ft_atoi ft_string ft_number
FT_PRINTF		+=	ft_print_strings ft_print_char ft_function_list
FT_PRINTF		+=	ft_print_num_u ft_print_num_s ft_specifier
				
PRINTF_SRCS	=	$(FT_PRINTF:=.c)
PRINTF_OBJS	=	$(addprefix build/, $(PRINTF_SRCS:.c=.o))


.PHONY: all clean fclean re

all: $(NAME)

build:
	@mkdir build/

$(NAME): $(PRINTF_OBJS)
	@ar rcs $@ $^

clean:
	@rm -rf build/

fclean: clean
	@rm -f $(NAME)

re: fclean all

build/%.o: %.c includes/ft_printf.h | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@
