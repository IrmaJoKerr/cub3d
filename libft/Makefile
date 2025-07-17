# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 16:34:11 by wjun-kea          #+#    #+#              #
#    Updated: 2025/07/16 05:39:55 by bleow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBRARY = libft

FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_strncpy.c get_next_line/get_next_line.c ft_strtol.c ft_realloc.c ft_strtok.c \
	ft_strcmp.c ft_fprintf/ft_fprintf.c ft_fprintf/ft_fprintf_utils.c ft_fprintf/ft_fprintf_utils_sub.c \
	ft_fprintf/ft_fprint_numbers.c ft_fprintf/ft_fprint_misc.c ft_fprintf/ft_fprint_hex.c \
	ft_isxdigit.c ft_strndup.c ft_isspace.c ft_strcat.c ft_strstr.c ft_strcpy.c ft_atoll.c \
	ft_arrlen.c ft_atoiarr_cln.c ft_atoiarr_errcln.c ft_atoierr.c ft_free_2d.c \
	ft_free_int_2d.c ft_intarrlen.c ft_safefree.c

OBJS = $(FILES:.c=.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
      ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
      ft_lstmap.c

BONUS_OBJS = $(BONUS:.c=.o)

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -std=c99

NAME = libft.a

all : $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Library has been created."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean : 
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "Object files removed."

fclean : clean 
	@$(RM) $(NAME)
	@echo "Library $(NAME) removed."

re : fclean all

bonus : $(OBJS) $(BONUS_OBJS) 
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "Bonus Library has been created."
	
so: $(OBJS) $(BONUS_OBJS)
	@echo "Compiling shared library libft.so"
	$(CC) -fPIC -shared -o libft.so $(OBJS) $(BONUS_OBJS)
	@echo "Shared library libft.so has been created."

.PHONY: all clean fclean re bonus
