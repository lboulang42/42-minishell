/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/31 17:19:01 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*Error Messages Macro*/
# ifndef MINI
#  define MINI "Minishell"
# endif
# ifndef ERR_MALL
#  define ERR_MALL "Malloc Error"
# endif
# ifndef ERR_SYNTX
#  define ERR_SYNTX "Syntax error near unexpected token"
# endif
# ifndef ERR_CLQUOTES
#  define ERR_CLQUOTES "Please close quotes"
# endif
# ifndef ERR_NOSUCHF
#  define ERR_NOSUCHF "No such file or directory"
# endif
# ifndef ERR_NOTDIR
#  define ERR_NOTDIR "not a directory"
# endif
# ifndef ERR_ISDIR
#  define ERR_ISDIR "Is a directory"
# endif
# ifndef ERR_CMD
#  define ERR_CMD "command not found"
# endif
# ifndef ERR_PERM
#  define ERR_PERM "Permission denied"
# endif
# ifndef ERR_NARGS
#  define ERR_NARGS "numeric argument required"
# endif
# ifndef ERR_TOOMARGS
#  define ERR_TOOMARGS "too many arguments"
# endif
# ifndef ERR_NVALID
#  define ERR_NVALID "not a valid identifier"
# endif
# ifndef ERR_AMBIGUS
#  define ERR_AMBIGUS "ambiguous redirect"
# endif

/*Variable Macro*/
# ifndef DQUOTE
#  define DQUOTE '"'
# endif
# ifndef SQUOTE
#  define SQUOTE '\''
# endif
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/*Exit Codes*/
# ifndef EXIT_MISS
#  define EXIT_MISS 2
# endif

/*Structure de liste-chainées pour l'env;*/
typedef struct s_env
{
	char			*name;
	char			*value;
	int				display;
	struct s_env	*next;
}					t_env;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				here_doc_fd;
}					t_redir;

/*Structure globale minishell*/
typedef struct s_all
{
	int				prev_fd;
	int				link_fd[2];
	int				default_out_fd;
	int				pid[1024];
	int				exit_code;
	char			*here_doc_buffer;
	char			*here_doc_line;
	char			*here_doc_limiter;
	int				here_doc_fd[2];
	char			*here_doc_readline;
	char			**all_lines;
	char			**tokens;
	char			*cmd;
	char			**arg;
	int				status;
	int				args_size;
	int				nbr_redir;
	int				index_redir;
	int				redir_before;
	char			*input;
	t_redir			*redir_list;
	t_env			*env;
}					t_all;

// int	openit(t_all *all, char **tokens, int i);
int					open_fd(t_all *all, char **tokens, int i);
int					get_status(t_all *all);
void				open_heredoc(t_all *all);
int					isredir(char *str);
void				free_redir_list(t_all *all);
int					handle_heredocbooste(t_all *all);
int					handle_heredoc2(t_all *all, char *limiter);
void				ft_free_heredoc2(t_all *all);
void				child_heredoc2(t_all *all);
void				init_redirlist(t_all *all, char *input);
/*builtin/*/

/*builtin/cd.c*/
int					cd(t_all *all, char **tokens);
int					do_cd(t_all *all, char *path);

/*builtin/echo.c*/
int					echo(char **tokens);

/*builtin/env.c*/
int					env(t_all *all);

/*builtin/exec_builtin.c*/
int					execute_builtin(t_all *all, int builtin_code);
int					is_builtin(char *cmd_name);

/*builtin/exit.c*/
void				ft_exit(t_all *all);
void				ft_exit_free(t_all *all, int exit_code);
void				exit_free_msg(t_all *all, int code, char *str1, char *str2);
unsigned long long	ft_atoilonglong(const char *str, const char *str_safe);
unsigned long long	do_atoi(const char *str, int neg, const char *str_safe);
/*builtin/export.c*/
void				do_export(t_all *all, char *key, char *value);
int					export(t_all *all);
int					parse_export(char *token);
int					print_export(t_all *all);
/*builtin/pwd.c*/
int					pwd(void);
/*builtin/unset.c*/
int					unset(t_all *all);

/*exec/*/
int					check_alone_pipes_start(char *str);
int					check_alone_pipes_end(char *str);
int					check_pipes(char *str);
/*exec/exec_acces.c*/
char				*ft_join_path(char *try_path, char *cmd_name);
void				ft_access_fail(char **PATHvaaaar, char *cmd_path,
						char *cmd_name);
char				*ft_check_acces(char **env_path, char *cmd_name, int i);
//fonction ATROCE
/*exec/exec_child.c*/
char				*get_path_putain(char *cmd, t_env *env);
void				redirection_execve(t_all *all, char **all_lines,
						int index_pipe);
void				ft_free_child(t_all *all, char **env_array, char *cmd_path,
						int status);
int					count_redir(char **tokens);
void				child(t_all *all, int index_pipe, int builtin_code);
/*exec/exec_utils.c*/
void				safeclose(int fd);
void				update_status_int(t_all *all, int status);
int					is_this_meta(char *s, char *metachar);
int					isdir(char *cmd_path, char *cmd_name);
/*exec/exec_main.c*/
void				start_exec(t_all *all);
void				handle_line(t_all *all, int index_pipe);
char				**get_env(t_env *env);
void				parent(t_all *all);
void				ft_kill_dir(char **PATHvar, char *cmd_path);
void				ft_free_only_builtin(t_all *all, int status);
void				only_builtin(t_all *all, int index_pipe, int builtin_code);

/*exec/here_doc.c*/
void				ft_free_heredoc(t_all *all);
void				wait_and_update(t_all *all, int pid);
void				child_heredoc(t_all *all);
int					handle_heredoc(t_all *all, int index_name);
/*exec/open_redir.c*/
int					handle_outfile_trunc(t_all *all);
int					handle_outfile_append(t_all *all);
int					handle_infile(t_all *all);
/*exec/exec_parse.c*/
int					parse(t_all *all, char **tab);
int					isredir(char *str);
int					mallocparse(t_all *all, char **tab);
void				printparse(char *cmd, char **arg, int *type, char **files);
/*exec/redirection_handler.c*/
int					get_outfile_infile_builtin2(t_all *all, char **tokens);
void				get_outfile_infile(t_all *all, char **tokens);
/*exec/signal.c*/
void				ctrlc(int sig);
void				ctrlchere_doc(int sig);
/*exec/tokenisation.c*/
void				inverse_all(char *str, int flag);
void				tokens_positif(char **tokens, int flag);
char				**kick_empty_tokens(char **tab);

/*main/*/

/*main/error.c*/
void				err_msg(char *err_msg, char *function_name); //unsed
/*main/init.c*/
t_all				*init_data(void);
/*main/main.c*/
int					main(int argc, char **argv, char **env);
void				run_easyshell(t_all *all);

/*parsing/*/
char				*toneg(char *str);
/*parsing/expand.c*/
int					append_char_and_spaces(char *tmp, char c, int j);
int					append_double_char_and_spaces(char *tmp, char c1, char c2,
						int j);
char				*insert_expansion(char *str, char *key_name,
						char *key_value, int index_variable);
char				*add_spaces_input(char *str);
char				*extract_key_name(char *str, int start);
//doit pas etre la
char				*get_value_by_key(t_env *full_env, char *key);
char				*expand_string(char *str, t_env *env);
/*parsing/handle_quotes.c*/
char				*delete_quote(char *input);
void				inverse_string(char *str, int flag);
/*parsing/parse.c*/
int					is_same_string(char *str1, char *str2);
/*parsing/syntax_error.c*/
int					check_alone_quote(char *str);
int					valid_rafters(char *str, int len);
int					check_rafters(char *str);
int					check_empty(char *str);
int					syntax_error(char *input);
/*parsing/utils_parsing.c*/
int					iswhitespace(const char c);
int					is_space(char c);
int					is_meta(char c);
int					is_quote(char c);
int					count_meta(char *input);
int					count_quote(char *input);
int					ft_strcmp(const char *s1, const char *s2);
int					valid_name(char c);

/*t_env/*/

/*t_env/t_env_init.c*/
char				*get_env_name(char *env_line);
char				*get_env_value(char *env_line, char *name);
void				init_env(t_all *data, char **env);
//surveiller si ca ca fait pas de dingz
void				free_t_env(t_env **env);
t_env				*t_env_new(char *name, char *value, int display);
/*t_env/t_env_operation.c*/
t_env				*get_last_t_env(t_env *env);
void				add_t_env(t_env **env, char *name, char *value,
						int display);
char				*get_key(t_env *full_env, char *key);

#endif