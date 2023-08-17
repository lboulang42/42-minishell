/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/17 18:35:22 by gcozigon         ###   ########.fr       */
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
# include <signal.h>

# define DQUOTE '"'
# define SQUOTE '\''


//temporaire :
# define ERR_KEY_VAL "No Value With This Key"
# define NO_ENV "No env Submitted in init_env()"
//


# ifndef ERR_MALL
#  define ERR_MALL "Minishell : Malloc Error"
# endif

# ifndef ERR_SYNTX
#  define ERR_SYNTX "Mini: Syntax error near unexpected token:"
# endif

# ifndef ERR_NOSUCHF
#  define ERR_NOSUCHF "No such file or directory"
# endif

# ifndef ERR_NOTDIR
#  define ERR_NOTDIR "not a directory"
# endif

# ifndef ERR_CMD
#  define ERR_CMD "command not found: "
# endif
# ifndef ERR_PERM
#  define ERR_PERM "permission denied"
# endif

typedef struct s_env
{
	char	*name;
	char	*value;
	struct s_env	*next;
}	t_env;

// typedef struct s_data
// {
// 	char	**m_env;
// 	int		status;
// 	char    **token;
//     int     n_lines;//nombre de lines differentes a exec (cat | echo) = 2 n_lines
//     int     n_cmd;//nombre de commandes a exec (echo  -n "magroz" "bite") = 4 n_cmd

// }	t_all;
#define MAX_ARGS 64 //a tej

typedef struct s_arguments
{
	char	*args[MAX_ARGS];
	int		count;
}	t_arguments;

typedef struct s_cmd
{
	char	**file;
	char	**args;
	char	*cmd;
	int		*type;
}			t_cmd;

typedef struct s_all
{
	// char	**env;
	char **default_env;
	char	**path;
	int		prev;
	int		link_fd[2];
	int		pid[1024];
	char	*path_cmd1;
	int		nbcmd;
	char	**tab;
	int		infile_fd;
	int		outfile_fd;

	int		exit_code;
	t_env	*env;
}			t_all;

/*NEW*/

/*exec/exec.c*/
void	exec_init(t_all *all, char *input);
void    handle_line(t_all *all, char *line, int total_pipes, int index_pipe);//tokenisation de con
char	*get_path_putain(char *cmd, t_env *env);
void	ft_access_fail(char *cmd_path, char *cmd_name);
char	*ft_join_path(char *try_path, char *cmd_name);
int is_this_meta(char *s, char *metachar);
int	count_meta(char *input);
int	is_meta(char c);
char *extract_key_name(char *str, int start);

/*exec/redirection handler*/
void	get_outfile_infile(t_all *all, char **tokens);
int handle_outfile_trunc(t_all *all, char **tokens_array, int index_name);
int handle_heredoc(t_all *all, char **tokens_array, int index_name);
int handle_infile(t_all *all, char **tokens_array, int index_name);
int handle_outfile_append(t_all *all, char **tokens_array, int index_name);
	
/*exec/tokenisation.c*/
void	tokens_positif(char **tokens);
char	**kick_empty_tokens(char **tab);
char	*ft_check_acces(char **env_path, char *cmd_name, int i);

/*main/init.c*/
void	init_shell(t_all *all, char **env);
/*main/main.c*/
int	main(int argc, char **argv, char **env);
void	run_easyshell(t_all *all, char **env);

void	ctrlc(int sig);
void	ctrld(int sig);

/*parsing/expand.c*/
char	*add_spaces_input(char *str);
char *expand_string(char *str, t_env *env);
int	append_char_and_spaces(char *tmp, char c, int j);
char *insert_expansion(char *str, char *key_name, char *key_value, int index_variable);
int	append_double_char_and_spaces(char *tmp, char c1, char c2, int j);

/*parsing/handle_quotes.c*/
void	inverse_string(char *str, int flag);
/*parsing/parse.c*/
int		is_same_string(char *str1, char *str2);

/*t_env/t_env_handler.c*/
void	init_env(t_all *data, char **env);
char    *get_key(t_env *full_env, char *key);
void	free_t_env(t_env **env);
void	add_t_env(t_env **env, char *name, char *value);
t_env	*t_env_new(char	*name, char *value);
t_env	*get_last_t_env(t_env *env);
void	print_t_env(t_env *env);
/**/

int	count_quote(char *input);

char	*delete_quote(char *input);

int	syntax_error(t_all *all, char *input);
/*main/erro.c*/
void    err_msg(char *err_msg, char *function_name);

// /*leo*/
// char	*find_cmd_2(t_all *all, char *cmd_name);
// void	exec_init(t_all *all, char *input);
// void	inverse_string(char *str, int flag);
// char	*ft_check_acces(char **env_path, char *cmd_name, int i);
// /*error_handler.c*/

// void	ft_err(char *err_msg);

// char    *get_value_by_key(t_env *full_env, char *key);

// /*envhandler.c*/
// void	init_env(t_all *data, char **env);
// void	print_t_env(t_env *env);
// t_env	*t_env_new(char	*name, char *value, int display);
// t_env	*get_last_t_env(t_env *env);
// void	add_t_env(t_env **env, char *name, char *value, int display);
// void	free_t_env(t_env **env);

// char		**keep_path(t_all *all);
// void		ft_free_split(char **tab);
// int			clean_args(t_all *all, char **av);
// int			pipex(t_all *all, char **av);
// char		*keep_access(t_all *all, int nb, char *cmd);
// char		*check_relative_paths(t_all *all, char **cmd_split);
// char		*check_absolute_path(char **cmd_split);
// char		*generate_test_path(char *path, char *cmd);
// void		ft_exec(t_all *all, int nb, char **tmp);
// void		free_split(char **tab);
// void		close_pipes(t_all *all);
// void		free_resources(t_all *all);
// void		ft_wait(t_all *all);
// int			open_error(t_all *all, char **cmd_args);
// char		*ft_strjoingnl(char *s1, char *s2);
// char		*ft_strcpy(char *dest, char *src);

// void		init_shell(t_all *all, char **env);
// void		run_easyshell(t_all *all, char **env);

// int			is_space(char c);
// int			is_meta(char c);
// int			append_char_and_spaces(char *tmp, char c, int j);
// int			append_double_char_and_spaces(char *tmp, char c1, char c2, int j);
// int			count_meta(char *input);
// int			count_quote(char *input);
// int			db_pipes(char *input);

// int		syntax_error(t_all *all, char *input);
// int			check_alone_quote(char *str);
// int			check_pipes(char *str);
// int			check_rafters(char *str);
// void	save_str_quote(char *input, int flag);

// void		init_token(t_all *all, char *input);
// void		token_recognition(t_all *all, char *input);
#endif