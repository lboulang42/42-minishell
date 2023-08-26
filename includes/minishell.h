/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/26 18:52:55 by gcozigon         ###   ########.fr       */
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
# include <errno.h>
#include <limits.h>



# define DQUOTE '"'
# define SQUOTE '\''
# define MINI "Minishell"
//temporaire :
# define ERR_KEY_VAL "No Value With This Key"
# define NO_ENV "No env Submitted in init_env()"
//


# define ERR_TOOMAN "too many arguments"
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
#  define ERR_CMD "command not found"
# endif
# ifndef ERR_PERM
#  define ERR_PERM "Permission denied"
# endif



#ifndef PATH_MAX
# define PATH_MAX 4096
#endif
# ifndef MAX_ARGS
#  define MAX_ARGS 64
# endif


# define EXIT_MISS 2
/*
Structure de liste-chainées pour l'env;
*/

typedef struct s_env
{
	char	*name;
	char	*value;
	int		display;
	struct s_env	*next;
}	t_env;


/*
Structure globale minishell
*/
typedef struct s_all
{
	int		prev;//used
	int		link_fd[2];//used
	int		pid[1024];//doit etre malloc et pas taille fixe, possible de faire plus de 1024 |
	int		btn_fd;
	int		exit_code;
	char	*here_doc_buffer;
	char	*here_doc_line;
	char	*here_doc_limiter;
	int		here_doc_fd[2];
	char *here_doc_readline;
	char **all_lines;
	int	default_out;
	char **tokens;
	t_env	*env;
}			t_all;


void    ft_exit_free(t_all *all);
char	*get_env_name(char *env_line);
char	*get_env_value(char *env_line, char *name);
//builtins

int	get_outfile_infile_builtin(t_all *all, char **tokens, char **all_lines);
int    cd(t_all *all, char **tokens);
int		echo(char **tokens);
int		is_builtin(char *cmd_name);
int		exec_builtin(char **tokens, t_all *all, int i, char **all_lines, int index_pipe);
void    ft_exit(t_all *all, char **tokens, char **all_lines);
int export(t_all *all, char **tokens);
void do_export(t_all *all, char *key, char *value);

int		pwd(void);
// int    unset(t_env *env, char **tokens);
int    unset(t_all *all, char **tokens);
int env(t_all *all);

void	 plug_builtin(char **tokens, t_all *all, int i, char **all_lines, int index_pipe);
int	execute_builtin(char **tokens, t_all *all, int i, char **all_lines);

unsigned long long	ft_atoilonglong(const char *str, const char *str_safe);
/*NEW*/

int	ft_strcmp(const char *s1, const char *s2);
char	*ft_get_file(char *buffer, int fd);
char	*ft_get_line(char *buffer);
int	ft_is_same_line(char *line, char *limiter);

char	*ft_update_buffer(char *buffer);
char	*ft_join_free(char *str1, char *str2);

/*exec/exec.c*/
void	exec_init(t_all *all, char *input);
void    handle_line(t_all *all, char **lines, int index_pipe);
char	*get_path_putain(char *cmd, t_env *env);
void	ft_access_fail(char **PATHvaaaar, char *cmd_path, char *cmd_name);
char	*ft_join_path(char *try_path, char *cmd_name);
int is_this_meta(char *s, char *metachar);
int	count_meta(char *input);
int	is_meta(char c);
char *extract_key_name(char *str, int start);
void ft_kill_dir(char **PATHvar, char *cmd_path, char *cmd_name);


/*exec/redirection handler*/
void	get_outfile_infile(t_all *all, char **tokens, char **all_lines, int index_pipe);
int handle_outfile_trunc(t_all *all, char **tokens_array, int index_name);
int handle_heredoc(t_all *all, char **tokens_array, int index_name, char **all_lines);
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

void	reactiv(int sig);
void	ctrlc(int sig);
void ctrldhere_doc(int sig);
t_all *init_data(void);

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
void	add_t_env(t_env **env, char *name, char *value, int display);
t_env	*t_env_new(char	*name, char *value, int display);
t_env	*get_last_t_env(t_env *env);
void	print_t_env(t_env *env);
/**/
int	count_quote(char *input);
char	*delete_quote(char *input);

int	syntax_error(t_all *all, char *input);
/*main/erro.c*/
void    err_msg(char *err_msg, char *function_name);

#endif