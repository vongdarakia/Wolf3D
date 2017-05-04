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

NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

FT_CHAR 		= 	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_isspace
FT_CHAR			+= 	ft_isbaseset ft_toupper ft_tolower

FT_CONVERSION	=	ft_itoa ft_atoi ft_atoi_base ft_atof

FT_LST			=	ft_lstnew ft_lstdelone ft_lstdel ft_lstadd
FT_LST			+=	ft_lstiter ft_lstmap

FT_MEM			=	ft_memmove ft_memcpy ft_memccpy ft_memcmp ft_memchr
FT_MEM			+=	ft_memset ft_memdel ft_memalloc ft_bzero

FT_NUM			=	ft_pow
			
FT_PUT			+=	ft_putchar ft_putstr ft_putendl ft_putnbr
FT_PUT			+=	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd

FT_SORT			=	ft_sortf

FT_STR			=	ft_strnew ft_strdup
FT_STR			+=	ft_strequ ft_strnequ
FT_STR			+=	ft_strdel ft_strclr
FT_STR			+=	ft_strcat ft_strncat ft_strlcat ft_strlen
FT_STR			+=	ft_strcpy ft_strncpy ft_strcmp ft_strncmp
FT_STR			+=	ft_strstr ft_strnstr ft_strchr ft_strrchr
FT_STR			+=	ft_strjoin ft_strsub ft_strsplit ft_strtrim
FT_STR			+=	ft_striter ft_striteri ft_strmap ft_strmapi
FT_STR			+=  ft_strndup ft_strnequ_case ft_strrealloc ft_word_count ft_isstrbaseset

CHAR_SRCS	=	$(addprefix ft_char/, $(FT_CHAR:=.c))
CONV_SRCS	=	$(addprefix ft_conversion/, $(FT_CONVERSION:=.c))
LST_SRCS	=	$(addprefix ft_lst/, $(FT_LST:=.c))
MEM_SRCS	=	$(addprefix ft_mem/, $(FT_MEM:=.c))
NUM_SRCS	=	$(addprefix ft_num/, $(FT_NUM:=.c))
PUT_SRCS	=	$(addprefix ft_put/, $(FT_PUT:=.c))
SORT_SRCS	=	$(addprefix ft_sort/, $(FT_SORT:=.c))
STR_SRCS	=	$(addprefix ft_str/, $(FT_STR:=.c))

CHAR_OBJS	=	$(addprefix build/, $(CHAR_SRCS:.c=.o))
CONV_OBJS	=	$(addprefix build/, $(CONV_SRCS:.c=.o))
LST_OBJS	=	$(addprefix build/, $(LST_SRCS:.c=.o))
MEM_OBJS	=	$(addprefix build/, $(MEM_SRCS:.c=.o))
NUM_OBJS	=	$(addprefix build/, $(NUM_SRCS:.c=.o))
PUT_OBJS	=	$(addprefix build/, $(PUT_SRCS:.c=.o))
SORT_OBJS	=	$(addprefix build/, $(SORT_SRCS:.c=.o))
STR_OBJS	=	$(addprefix build/, $(STR_SRCS:.c=.o))

LIB_OBJS	=	$(CHAR_OBJS)
LIB_OBJS	+=	$(CONV_OBJS)
LIB_OBJS	+=	$(LST_OBJS)
LIB_OBJS	+=	$(MEM_OBJS)
LIB_OBJS	+=	$(NUM_OBJS)
LIB_OBJS	+=	$(PUT_OBJS)
LIB_OBJS	+=	$(SORT_OBJS)
LIB_OBJS	+=	$(STR_OBJS)

.PHONY: all clean fclean re

all: $(NAME)

build:
	@mkdir build/
	@mkdir build/ft_char/
	@mkdir build/ft_conversion/
	@mkdir build/ft_lst/
	@mkdir build/ft_mem/
	@mkdir build/ft_num/
	@mkdir build/ft_put/
	@mkdir build/ft_sort/
	@mkdir build/ft_str/

$(NAME): $(LIB_OBJS)
	@ar rcs $@ $^

clean:
	@rm -rf build/

fclean: clean
	@rm -f $(NAME)

re: fclean all

build/ft_char/%.o: ft_char/%.c includes/ | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@

build/ft_conversion/%.o: ft_conversion/%.c includes/ | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@

build/ft_lst/%.o: ft_lst/%.c includes/ | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@

build/ft_mem/%.o: ft_mem/%.c includes/ | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@

build/ft_num/%.o: ft_num/%.c includes/ | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@

build/ft_put/%.o: ft_put/%.c includes/ | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@

build/ft_sort/%.o: ft_sort/%.c includes/ | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@

build/ft_str/%.o: ft_str/%.c includes/ | build
	$(CC) -c -I includes/ $(CFLAGS) $< -o $@
