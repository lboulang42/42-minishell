# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 19:43:05 by lboulang          #+#    #+#              #
#    Updated: 2023/08/31 15:57:07 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 			minishell

SRCS_NAMES 		=	exec/exec_main.c\
					exec/exec_utils.c\
					exec/exec_child.c\
					exec/exec_acces.c\
					exec/exec_heredoc.c\
					exec/tokenisation.c\
					exec/rebuild_env.c\
					exec/exec_parse.c\
					exec/redirections_builtin.c\
					exec/redirection_exec.c\
					exec/signal.c\
					exec/here_doc.c\
					exec/open_redir.c\
					main/init.c\
					main/main.c\
					main/error.c\
					parsing/expand.c\
					parsing/syntax_error.c\
					parsing/syntax_pipes.c\
					parsing/redir_list.c\
					parsing/utils_syntax.c\
					parsing/handle_quotes.c\
					parsing/utils_parsing.c\
					parsing/utils_parsing2.c\
					t_env/t_env_operation.c\
					t_env/t_env_init.c\
					builtin/cd.c\
					builtin/echo.c\
					builtin/exec_builtin.c\
					builtin/exit.c\
					builtin/export.c\
					builtin/pwd.c\
					builtin/unset.c\
					builtin/env.c\

# pipex/utils1.c
# pipex/utils2.c pipex/utils3.c pipex/pipex.c

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
	$(CC) $(CFLAGS) ${INC} $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[31;5mminishell\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/builtin
	mkdir -p objs/exec
	mkdir -p objs/main
	mkdir -p objs/parsing
	mkdir -p objs/t_env
	mkdir -p objs/builtin

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