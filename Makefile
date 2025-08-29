# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 12:29:47 by bleow             #+#    #+#              #
#    Updated: 2025/08/29 15:56:51 by bleow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_DIR = srcs
OBJ_DIR = objs

COLLISIONS_SRCS = \
	$(SRC_DIR)/collisions/calculate_tile_position.c \
	$(SRC_DIR)/collisions/calculate_view.c \
	$(SRC_DIR)/collisions/tile_move.c

EXECUTION_SRCS = \
	$(SRC_DIR)/execution/door_utils.c \
	$(SRC_DIR)/execution/draw_space.c \
	$(SRC_DIR)/execution/minimap_draw_player.c \
	$(SRC_DIR)/execution/minimap_setup.c \
	$(SRC_DIR)/execution/minimap_utils.c \
	$(SRC_DIR)/execution/minimap.c \
	$(SRC_DIR)/execution/raycasting_floor.c \
	$(SRC_DIR)/execution/raycasting_setup.c \
	$(SRC_DIR)/execution/raycasting_utils.c \
	$(SRC_DIR)/execution/render_colum.c \
	$(SRC_DIR)/execution/render_doors.c

HOOKS_SRCS = \
	$(SRC_DIR)/hooks/hooks_look.c \
	$(SRC_DIR)/hooks/hooks_mouse.c \
	$(SRC_DIR)/hooks/hooks_movement.c \
	$(SRC_DIR)/hooks/keyhooks_a.c \
	$(SRC_DIR)/hooks/keyhooks_b.c

PARSING_SRCS = \
	$(SRC_DIR)/parsing/cleanup_a.c \
	$(SRC_DIR)/parsing/cleanup_b.c \
	$(SRC_DIR)/parsing/config_parser.c \
	$(SRC_DIR)/parsing/cub3D.c \
	$(SRC_DIR)/parsing/initstructs.c \
	$(SRC_DIR)/parsing/load_textures.c \
	$(SRC_DIR)/parsing/map_parser.c \
	$(SRC_DIR)/parsing/map_validation_utils.c \
	$(SRC_DIR)/parsing/map_validation.c \
	$(SRC_DIR)/parsing/parse_colors.c \
	$(SRC_DIR)/parsing/parse_path.c \
	$(SRC_DIR)/parsing/parse_settings.c \
	$(SRC_DIR)/parsing/parse_texture.c \
	$(SRC_DIR)/parsing/parser_utils.c \
	$(SRC_DIR)/parsing/parser.c \
	$(SRC_DIR)/parsing/populate_map.c

SRCS = $(COLLISIONS_SRCS) $(EXECUTION_SRCS) $(HOOKS_SRCS) $(PARSING_SRCS)

COLLISIONS_OBJS = $(COLLISIONS_SRCS:$(SRC_DIR)/collisions/%.c=$(OBJ_DIR)/collisions/%.o)
EXECUTION_OBJS = $(EXECUTION_SRCS:$(SRC_DIR)/execution/%.c=$(OBJ_DIR)/execution/%.o)
HOOKS_OBJS = $(HOOKS_SRCS:$(SRC_DIR)/hooks/%.c=$(OBJ_DIR)/hooks/%.o)
PARSING_OBJS = $(PARSING_SRCS:$(SRC_DIR)/parsing/%.c=$(OBJ_DIR)/parsing/%.o)

OBJS = $(COLLISIONS_OBJS) $(EXECUTION_OBJS) $(HOOKS_OBJS) $(PARSING_OBJS)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -gdwarf-4
SANITIZE_FLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

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

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: re

.PHONY: all clean fclean re debug sanitize
