# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/15 11:35:49 by bcosters          #+#    #+#              #
#    Updated: 2021/09/08 15:22:43 by bcosters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	~ Philosophers (BONUS) ~	#

# -*- Definitions of variables -*-

NAME	= philo_bonus

OBJDR	= obj/

HEADER	= philo_bonus.h

MAINSRC	= philo_bonus.c
SRCS	= ${shell find src -type f -name "*.c"}
OBJS	= ${SRCS:src/%.c=obj/%.o}
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -pthread #-fsanitize=thread -g

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
			@$(CC) $(CFLAGS) $(MAINSRC) ${wildcard src/*.c} -o $(NAME)
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
