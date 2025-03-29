# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 16:34:32 by ypacileo          #+#    #+#              #
#    Updated: 2024/07/15 17:15:37 by ypacileo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
OBJ = ft_basic.o ft_printf.o
INCLUDE = libftprintf.h
all: $(NAME)

$(NAME) : $(OBJ) $(INCLUDE)
	$(AR) $(NAME) $(OBJ)

%.o : %.c
	gcc  -c  $(CFLAGS) $< -o $@

clean :
	${RM} ${OBJ}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY: all clean fclean re
