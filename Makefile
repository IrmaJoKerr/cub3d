# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 12:29:47 by bleow             #+#    #+#              #
#    Updated: 2025/07/05 12:39:06 by bleow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -gdwarf-4
DEBUG_FLAGS = -gdwarf-4
SANITIZE_FLAGS = -fsanitize=address,undefined

LIBFT_DIR = libft
MLX_DIR = ../minilibx-linux
CUB3D_DIR = srcs
INCLUDE_DIRS = includes $(LIBFT_DIR)/includes
INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

CUB3D_SRCS = srcs/cub3D.c \
			 srcs/cleanup.c \
			 srcs/initstructs.c \
			 srcs/input_validation.c \
			 srcs/map_validation.c \
			 srcs/movehero.c \
			 srcs/parser.c \
			 srcs/parserutil_a.c \
			 srcs/parserutil_b.c 

CUB3D_OBJS_DIR = objects
CUB3D_OBJS = $(CUB3D_SRCS:srcs/%.c=$(CUB3D_OBJS_DIR)/%.o)

$(CUB3D_OBJS_DIR):
	@mkdir -p $(CUB3D_OBJS_DIR)

$(CUB3D_OBJS_DIR)/%.o: srcs/%.c | $(CUB3D_OBJS_DIR)
	 @echo "Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

OBJS = $(CUB3D_OBJS)

all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJS) | $(CUB3D_OBJS_DIR)
	@echo "Linking $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext -o $(NAME)

$(LIBFT_DIR)/libft.a:
	@echo "Building libft"
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "Cleaning up..."
	rm -rf objects
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Performing full clean..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: re

default: all

.PHONY: all clean fclean re debug sanitize