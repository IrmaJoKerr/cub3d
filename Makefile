# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 12:29:47 by bleow             #+#    #+#              #
#    Updated: 2025/07/11 22:40:56 by wjun-kea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_DIR = srcs/parsing
OBJ_DIR = objs

SRCS = $(SRC_DIR)/cleanup.c \
	   $(SRC_DIR)/cub3D.c \
	   $(SRC_DIR)/initstructs.c \
	   $(SRC_DIR)/input_validation.c \
	   $(SRC_DIR)/map_validation.c \
	   $(SRC_DIR)/movehero.c \
	   $(SRC_DIR)/parse_path.c \
	   $(SRC_DIR)/parser.c \
	   $(SRC_DIR)/parserutil_a.c \
	   $(SRC_DIR)/parserutil_b.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBX_DIR = minilibx-linux
LIBX = $(LIBX_DIR)/libmlx_Linux.a

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(LIBX_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) \
		-L$(LIBX_DIR) -l:libmlx_Linux.a -lXext -lX11 -o $(NAME)
	@echo "$(NAME) has been created."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(LIBFT_DIR)/*.c $(LIBFT_DIR)/*.h
	@make bonus -C $(LIBFT_DIR)

$(LIBX):
	@make -C $(LIBX_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBX_DIR)
	$(RM) $(OBJS)
	@echo "Object files removed."

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(LIBX_DIR)
	$(RM) $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
