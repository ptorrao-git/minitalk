# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/23 11:38:55 by ptorrao-          #+#    #+#              #
#    Updated: 2024/07/25 15:54:47 by ptorrao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE			= -I include
CC				= cc -g
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -fPIC
LIBFT			= libft/libft.a
NAMEC			= client
NAMES			= server
SRCC			= client.c
SRCS			= server.c
OBJC 			= $(SRCC:.c=.o)
OBJS 			= $(SRCS:.c=.o)

all:			$(NAMES) $(NAMEC)

$(NAMEC):		$(OBJC) $(LIBFT)
				$(CC) -o $@ $(OBJC) -Llibft -lft

$(NAMES):		$(OBJS) $(LIBFT)
				$(CC) -o $@ $(OBJS) -Llibft -lft

%.o: 			%.c
				$(CC) -c $(CFLAGS) $< -o $@

$(LIBFT):
				make -C libft

clean:
				$(RM) $(OBJS) $(OBJC)
				make -C libft clean

fclean: 		clean
				$(RM) $(NAMES) $(NAMEC)
				make -C libft fclean

re: 			fclean all

.PHONY: 		all clean fclean re