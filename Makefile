# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 19:43:05 by lboulang          #+#    #+#              #
#    Updated: 2023/07/11 19:49:04 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME
NAME = 			minishell
NAME_BONUS =	 minishell_bonus
#LIBRARIES
LIBFT = 		./libft/libft.a
#SOURCES
SRCS =	main.c
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