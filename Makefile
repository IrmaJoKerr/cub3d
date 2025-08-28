# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 12:29:47 by bleow             #+#    #+#              #
#    Updated: 2025/08/28 21:57:17 by bleow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_DIR = srcs
OBJ_DIR = objs

PARSING_SRCS = $(wildcard $(SRC_DIR)/parsing/*.c)
HOOKS_SRCS = $(wildcard $(SRC_DIR)/hooks/*.c)
COLLISIONS_SRCS = $(wildcard $(SRC_DIR)/collisions/*.c)
EXECUTION_SRCS = $(wildcard $(SRC_DIR)/execution/*.c)

SRCS = $(PARSING_SRCS) $(HOOKS_SRCS) $(COLLISIONS_SRCS) $(EXECUTION_SRCS)

PARSING_OBJS = $(PARSING_SRCS:$(SRC_DIR)/parsing/%.c=$(OBJ_DIR)/parsing/%.o)
HOOKS_OBJS = $(HOOKS_SRCS:$(SRC_DIR)/hooks/%.c=$(OBJ_DIR)/hooks/%.o)
COLLISIONS_OBJS = $(COLLISIONS_SRCS:$(SRC_DIR)/collisions/%.c=$(OBJ_DIR)/collisions/%.o)
EXECUTION_OBJS = $(EXECUTION_SRCS:$(SRC_DIR)/execution/%.c=$(OBJ_DIR)/execution/%.o)

OBJS = $(PARSING_OBJS) $(HOOKS_OBJS) $(COLLISIONS_OBJS) $(EXECUTION_OBJS)

CC = gcc
RM = rm -f
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBX_DIR = minilibx-linux
LIBX = $(LIBX_DIR)/libmlx_Linux.a

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(LIBX_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) \
		-L$(LIBX_DIR) -l:libmlx_Linux.a -lXext -lX11 -lm -o $(NAME)
	@echo "$(NAME) has been created."

$(OBJ_DIR)/parsing/%.o: $(SRC_DIR)/parsing/%.c
	@mkdir -p $(OBJ_DIR)/parsing
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/hooks/%.o: $(SRC_DIR)/hooks/%.c
	@mkdir -p $(OBJ_DIR)/hooks
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/collisions/%.o: $(SRC_DIR)/collisions/%.c
	@mkdir -p $(OBJ_DIR)/collisions
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/execution/%.o: $(SRC_DIR)/execution/%.c
	@mkdir -p $(OBJ_DIR)/execution
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(LIBFT_DIR)/*.c $(LIBFT_DIR)/*.h
	@make bonus -C $(LIBFT_DIR)

$(LIBX):
	@make -C $(LIBX_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBX_DIR)
	$(RM) -r $(OBJ_DIR)
	@echo "Object files and directories removed."

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(LIBX_DIR)
	$(RM) $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
