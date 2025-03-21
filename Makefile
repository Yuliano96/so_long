# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 05:32:19 by yuliano           #+#    #+#              #
#    Updated: 2025/03/16 13:16:25 by yuliano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
OBJ_DIR = ./obj
SRC_DIR = ./src
CFLAGS = -Wall -Wextra -Werror -I./libft -I./ -I./minilibx-linux
LIBS = libft/libft.a ./minilibx-linux/libmlx.a -lX11 -lXext -lm

OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/error.o \
       $(OBJ_DIR)/map_validation.o \
       $(OBJ_DIR)/map_validate_path.o \
       $(OBJ_DIR)/read_map.o \
       $(OBJ_DIR)/utils.o \
       $(OBJ_DIR)/util2.o \
       $(OBJ_DIR)/util3.o

all: libs $(NAME)
	
# Compila o recompila la libft
libs:
	@make -C libft
	@make -C minilibx-linux

# Compila el programa principal
$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "✅ DONE"

# Compila los archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc -c $(CFLAGS) $< -o $@

# Limpieza de archivos objeto
clean:
	@make clean -C libft
	@make clean -C minilibx-linux
	rm -fr $(OBJ_DIR)

# Limpieza total (incluye libft.a y el ejecutable)
fclean: clean
	@make fclean -C libft
	rm -f $(NAME) 
	@echo "✅ CLEAN DONE"

# Reconstrucción completa
re: fclean all

.PHONY: all clean fclean
