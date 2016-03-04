# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/04 18:49:05 by bsouchet          #+#    #+#              #
#    Updated: 2016/03/04 14:43:14 by bsouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = fdf

FLAGS = -Wall -Wextra -Werror -O3

LIBFT = libft

DIR_S = sources

DIR_O = temporary

DIR_LIB = libraries

HEADERS = includes

SOURCES = main.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: temporary $(NAME)

$(NAME): $(OBJS)
	@make -C $(DIR_LIB)/$(LIBFT)
	@$(CC) $(FLAGS) -L $(DIR_LIB)/$(LIBFT) -lft -o $@ $^ -lmlx -framework OpenGL -framework AppKit

temporary:
	@mkdir -p temporary

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADERS)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

norme:
	@make norme -C $(DIR_LIB)/$(LIBFT)
	@echo
	norminette $(HEADERS)
	@echo
	norminette $(DIR_S)

clean:
	@rm -f $(OBJS)
	@make clean -C $(DIR_LIB)/$(LIBFT)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(DIR_LIB)/$(LIBFT)

re: fclean all

.PHONY: all, temporary, norme, clean, fclean, re
