# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 19:43:05 by lboulang          #+#    #+#              #
#    Updated: 2023/07/15 15:24:51 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME
NAME = 			minishell
NAME_BONUS =	 minishell_bonus
#LIBRARIES
LIBFT = 		./libft/libft.a
#SOURCES
SRCS =	./srcs/exec/main.c
SRCS_BONUS =	
#OBJECTS
OBJS = ${SRCS:.c=.o }
OBJS_BONUS = ${SRCS_BONUS:.c=.o }
#COMPILER
CC = @ gcc
CFLAGS = -g3 -Wall -Werror -Wextra -I .
#VISUAL
BOLD_TEXT = \033[1m
RESET_TEXT = \033[0m

all: ${NAME}

$(NAME) : ${OBJS}
	@make --no-print-directory  -C ./libft/
	$(CC) ${OBJS} ${LIBFT} -o ${NAME}
	@echo "MINISHELL $(BOLD_TEXT)MANDATORY$(RESET_TEXT) MAKED ✅\n"
	
# bonus : ${OBJS_BONUS}
# 	@make --no-print-directory  -C ./libft/
# 	@$(CC) ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}
# 	@echo "PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) MAKED ✅\n"
	

clean : 
	@make --no-print-directory clean -C ./libft/
	@rm -rf ${OBJS} 
	@echo "MINISHELL $(BOLD_TEXT)MANDATORY$(RESET_TEXT) CLEANED 🚮\n"
#	@rm -rf ${OBJS_BONUS} 
#	@echo "PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) CLEANED 🚮\n"
	
fclean : clean
	@rm -rf ${LIBFT}
	@echo "$(BOLD_TEXT)LIBFT$(RESET_TEXT) FCLEANED 🚮\n"
	@rm -rf ${NAME}
	@echo "MINISHELL $(BOLD_TEXT)MANDATORY$(RESET_TEXT) FCLEANED 🚮\n"
#	@rm -rf ${NAME_BONUS}
#	@echo "PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) FCLEANED 🚮\n"

re : fclean all

.PHONY : all bonus clean fclean re
=======
#    By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 19:43:05 by lboulang          #+#    #+#              #
#    Updated: 2023/07/15 22:36:39 by gcozigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 			minishell

SRCS_NAMES 		=	main.c tmp.c \
					pipex/utils1.c pipex/utils2.c pipex/utils3.c pipex/pipex.c

LIBFT			=	libft.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs


OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes -Ilibft

LIB				=	-lreadline -lm -Llibft -lft 

CC				=	cc

CDFLAGS 		= -MMD -MP

CFLAGS			=	-g3 -Wall -Werror -Wextra

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS)
	make -C libft
	$(CC) -g3 ${INC} $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[31;5mminishell\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) -g3 $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/pipex

clean:
	make clean -C libft
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${NAME}

leaks: ${NAME}
	clear && valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

leask: $(NAME)
	clear && valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

env: $(NAME)
	env -i ./minishell

stop:
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus leaks stop
>>>>>>> 2168ca81c5cec8ffe3daa3fe5050ad794b7ab53c
