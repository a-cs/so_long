# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 22:10:42 by acarneir          #+#    #+#              #
#    Updated: 2022/02/17 00:00:42 by acarneir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = clang

FLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lX11 -lXext -lmlx

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx_linux
MLX = $(MLX_DIR)/libmlx.a

INCLUDE_DIR = ./include
INCLUDE = -I $(INCLUDE_DIR)

SRC_DIR = ./src
SRCS = main.c \
	check_args.c \
	print_error.c \
	map.c \
	check_map.c \
	key_hooks.c \
	game.c

OBJ_DIR = ./objs
OBJS := $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))


all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) -lm $(OBJS) $(LIBFT) -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean: 
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re : fclean all