/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/28 15:29:51 by gcozigon         ###   ########.fr       */
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

typedef struct s_env
{
	char	*name;
	char	*value;
	int		display;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char	**m_env;
	int		status;
	char    **token;
    int     n_lines;//nombre de lines differentes a exec (cat | echo) = 2 n_lines
    int     n_cmd;//nombre de commandes a exec (echo  -n "magroz" "bite") = 4 n_cmd
	t_env	*env;
}	t_data;


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

/*error_handler.c*/

void	ft_err(char *err_msg);

/*envhandler.c*/
void	init_env(t_data *data, char **env);
void	print_t_env(t_env *env);
t_env	*t_env_new(char	*name, char *value, int display);
t_env	*get_last_t_env(t_env *env);
void	add_t_env(t_env **env, char *name, char *value, int display);
void	free_t_env(t_env **env);

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

int			is_space(char c);
int			is_meta(char c);
int			append_char_and_spaces(char *tmp, char c, int j);
int			append_double_char_and_spaces(char *tmp, char c1, char c2, int j);
int			count_meta(char *input);
int			count_quote(char *input);

void		syntax_error(t_all *all, char *input);
int			check_alone_quote(t_all *all, char *str);
int			check_pipes(t_all *all, char *input);
int			check_rafters(t_all *all, char *input);

void		init_token(t_all *all, char *input);
void		token_recognition(t_all *all, char *input);
#endif