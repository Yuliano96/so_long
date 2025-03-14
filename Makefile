# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 05:32:19 by yuliano           #+#    #+#              #
#    Updated: 2025/03/11 07:11:25 by yuliano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
OBJ_DIR = ./obj
SRC_DIR = ./src
CFLAGS = -Wall -Wextra -Werror -I./libft -I./
LIBS = libft/libft.a

OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/error.o \
       $(OBJ_DIR)/map_validation.o \
       $(OBJ_DIR)/read_map.o \
       $(OBJ_DIR)/utils.o

all: libs $(NAME)
	@echo "✅ DONE"

# Compila o recompila la libft
libs:
	@make -C libft

# Compila el programa principal
$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# Compila los archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc -c $(CFLAGS) $< -o $@

# Limpieza de archivos objeto
clean:
	@make clean -C libft
	rm -fr $(OBJ_DIR)

# Limpieza total (incluye libft.a y el ejecutable)
fclean: clean
	@make fclean -C libft
	rm -f $(NAME) 
# Reconstrucción completa
re: fclean all

.PHONY: all clean fclean re libs
