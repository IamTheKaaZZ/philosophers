# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/15 11:35:49 by bcosters          #+#    #+#              #
#    Updated: 2021/07/29 13:37:23 by bcosters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	~ Philosophers ~	#

# -*- Definitions of variables -*-

NAME	= philo

OBJDR	= obj/

HEADER	= philo.h

MAINSRC	= philo.c
SRCS	= ${shell find src -type f -name "*.c"}
OBJS	= ${SRCS:src/%.c=obj/%.o}

CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -pthread

# -*- The Rules -*-

#	Implicit rules

%.o: %.c	$(HEADER)
			@$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/%.c $(HEADER)
			@echo Compiling object $@
			@$(CC) $(CFLAGS) -c $< -o $@

#	Active rules

all:		$(NAME)

$(NAME):	$(OBJDR) $(OBJS) $(HEADER)
			@$(CC) $(CFLAGS) $(MAINSRC) ${wildcard src/*.c} -o $(NAME)
			#--------------------------------#
			@echo "Finished compiling MANDATORY $(NAME)"

bonus:		$(NAME)
			@$(CC) $(CFLAGS) -g $(MAINSRC) ${wildcard src/*.c} -o $(NAME)
			#--------------------------------#
			@echo "Finished compiling BONUS $(NAME)"

$(OBJDR):
			@mkdir -p $(OBJDR)

#	Cleaning rules

clean:
			@echo Removing all object files
			@rm -rf ${OBJDR}

fclean:		clean
			@echo "Removing $(NAME)"
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
