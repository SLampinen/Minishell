# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 11:47:29 by slampine          #+#    #+#              #
#    Updated: 2023/08/21 09:25:44 by slampine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES = main.c lexer.c
OBJECTS = $(SOURCES:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra 

all: $(NAME)

$(NAME): $(OBJECTS) minishell.h
	$(MAKE) -C libft
	cc $(CFLAGS) $(OBJECTS) $(INCLUDE) -o $(NAME) libft/libft.a -lreadline

clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJECTS)
fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)
	rm -f libft.a

re: fclean all

.PHONY: all clean fclean re
