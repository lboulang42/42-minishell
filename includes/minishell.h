/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/15 22:39:11 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define DQUOTE '"'
# define SQUOTE '\''
// > TYPE 1
// >> TYPE 2
// < TYPE 3
// << TYPE 4

typedef struct s_cmd
{
	char	**file;
	char	**args;
	char	*cmd;
	int		*type;
}			t_cmd;

typedef struct s_all
{
	char	**env;
	char	**path;
	int		prev;
	int		pipe_fd[2];
	int		pid[1024];
	char	*path_cmd1;
	int		nbcmd;

	char	**tab;
}			t_all;

char		**keep_path(t_all *all);
void		ft_free_split(char **tab);
int			clean_args(t_all *all, char **av);
int			pipex(t_all *all, char **av);
char		*keep_access(t_all *all, int nb, char *cmd);
void		ft_check_acces(char *path, char *cmd_name);
char		*check_relative_paths(t_all *all, char **cmd_split);
char		*check_absolute_path(char **cmd_split);
char		*generate_test_path(char *path, char *cmd);
void		ft_exec(t_all *all, int nb, char **tmp);
void		free_split(char **tab);
void		close_pipes(t_all *all);
void		free_resources(t_all *all);
void		ft_wait(t_all *all);
int			open_error(t_all *all, char **cmd_args);
char		*ft_strjoingnl(char *s1, char *s2);
char		*ft_strcpy(char *dest, char *src);

void		init_shell(t_all *all, char **env);
void		run_easyshell(t_all *all, char **env);
int			check_alone_quote(t_all *all, char *str);
#endif