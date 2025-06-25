# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: victor <victor@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 12:03:22 by vdiez-cu          #+#    #+#              #
#    Updated: 2025/06/25 14:13:26 by victor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRCS		= 	main.c \
			ft_split.c \
			path.c \
			pipex_utils.c

INCLUDE = ./pipex.h

OBJS		= $(SRCS:.c=.o)

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re