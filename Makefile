# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 05:32:19 by yuliano           #+#    #+#              #
#    Updated: 2025/03/29 12:56:05 by ypacileo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
OBJ_DIR = ./obj
SRC_DIR = ./src
CFLAGS = -Wall -Wextra -Werror -I./libft -I./ -I./mlx -I./ft_printf
LIBS = libft/libft.a ft_printf/libftprintf.a ./mlx/libmlx.a -lX11 -lXext -lm

OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/error.o \
       $(OBJ_DIR)/map_validation.o \
       $(OBJ_DIR)/map_validate_path.o \
       $(OBJ_DIR)/read_map.o \
       $(OBJ_DIR)/utils.o \
       $(OBJ_DIR)/util2.o \
       $(OBJ_DIR)/util3.o \
	   $(OBJ_DIR)/draw_map.o \
	   $(OBJ_DIR)/mover_player.o

all: libs $(NAME)
	
# Compila o recompila la libft
libs:
	@make -C libft
	@make -C mlx
	@make -C ft_printf

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
	@make clean -C mlx
	rm -fr $(OBJ_DIR)

fclean: clean
	@make fclean -C libft
	@make fclean -C ft_printf
	@make clean -C mlx
	rm -f mlx/libmlx.a
	rm -f $(NAME)
	@echo "✅ CLEAN DONE"


# Reconstrucción completa
re: fclean all

.PHONY: all clean fclean
