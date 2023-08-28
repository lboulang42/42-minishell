/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/28 12:59:19 by lboulang         ###   ########.fr       */
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
}	t_env;

/*Structure globale minishell*/
typedef struct s_all
{
	int		prev;
	int		link_fd[2];
	int		pid[1024];//doit etre malloc et pas taille fixe, possible de faire plus de 1024 |
	int		btn_fd;
	int		exit_code;
	char	*here_doc_buffer;
	char	*here_doc_line;
	char	*here_doc_limiter;
	int		here_doc_fd[2];
	char	*here_doc_readline;
	char	**all_lines;
	int		default_out;
	char	**tokens;
	char	*cmd; // [ls]
	char	**arg; // {[ls][-R]}
	char	**files; // {"out", "out2"}
	int		*type; // {1, 2};   // > out ls >> out2 -R //| cat -e < avion 
	int		status;
	t_env	*env;
}			t_all;

/*builtin/*/

/*builtin/cd.c*/
int		cd(t_all *all, char **tokens);
int		do_cd(t_all *all, char *path);
/*builtin/echo.c*/
int		echo(char **tokens);
/*builtin/env.c*/
int		env(t_all *all);
/*builtin/exec_builtin.c*/
int		execute_builtin(t_all *all, int builtin_code);
int		is_builtin(char *cmd_name);
/*builtin/exit.c*/ //clean et add last exit_code in ft_exit()
void	ft_exit(t_all *all);
void	ft_exit_free(t_all *all);
unsigned long long	ft_atoilonglong(const char *str, const char *str_safe);
unsigned long long	do_atoi(const char *str, int neg, const char *str_safe);
/*builtin/export.c*/
void	do_export(t_all *all, char *key, char *value);
int		export(t_all *all);
int		parse_export(char *token);
int		print_export(t_all *all);
/*builtin/pwd.c*/
int		pwd(void);
/*builtin/unset.c*/
int		unset(t_all *all);

/*exec/*/

/*exec/exec_acces.c*/
char	*ft_join_path(char *try_path, char *cmd_name);
void	ft_access_fail(char **PATHvaaaar, char *cmd_path, char *cmd_name);
char	*ft_check_acces(char **env_path, char *cmd_name, int i);//fonction ATROCE
/*exec/exec_child.c*/
char	*get_path_putain(char *cmd, t_env *env);
void	redirection_execve(t_all *all, char **all_lines, int index_pipe);
void	ft_free_child(t_all *all, char **env_array, char *cmd_path);
void	child(t_all *all, int index_pipe, int builtin_code);
/*exec/exec_utils.c*/
void	safeclose(int fd);
void	update_status_int(t_all *all, int status);
int		is_this_meta(char *s, char *metachar);
int     file_is_directory(char *cmd_path, char *cmd_name);
/*exec/exec_main.c*/
void	exec_init(t_all *all, char *input);
void    handle_line(t_all *all, int index_pipe);
char	**get_env(t_env *env);
void	parent(t_all *all);
void	ft_kill_dir(char **PATHvar, char *cmd_path, char *cmd_name);
void	ft_free_only_builtin(t_all *all, int status);
void	only_builtin(t_all *all, int index_pipe, int builtin_code);

/*exec/here_doc.c*/
void	ft_free_heredoc(t_all *all);
void	wait_and_update(t_all *all, int pid);
void	child_heredoc(t_all *all);
int		handle_heredoc(t_all *all, int index_name);
/*exec/open_redir.c*/
int		handle_outfile_trunc(t_all *all, int index_name);
int		handle_outfile_append(t_all *all, int index_name);
int		handle_infile(t_all *all, int index_name);
/*exec/parse.c*/
int		isredir(char *str);
void	*mallocparse(t_all *all, char **tab);
void	printparse(char *cmd, char **arg, int *type, char **files);
void	*parse(t_all *all, char **tab);
/*exec/redirection_handler.c*/
int		get_outfile_infile_builtin(t_all *all, char **tokens, char **all_lines);
void	get_outfile_infile(t_all *all, char **tokens, char **all_lines, int index_pipe);
/*exec/signal.c*/
void	ctrlc(int sig);
void	ctrlchere_doc(int sig);
/*exec/tokenisation.c*/
void	inverse_all(char *str, int flag);
void	tokens_positif(char **tokens, int flag);
char	**kick_empty_tokens(char **tab);

/*main/*/

/*main/error.c*/
void	err_msg(char *err_msg, char *function_name);//unsed
/*main/init.c*/
t_all *init_data(void);
/*main/main.c*/
int		main(int argc, char **argv, char **env);
void	run_easyshell(t_all *all);


/*parsing/*/

/*parsing/expand.c*/
int		append_char_and_spaces(char *tmp, char c, int j);
int		append_double_char_and_spaces(char *tmp, char c1, char c2, int j);
char	*insert_expansion(char *str, char *key_name, char *key_value, int index_variable);
char	*add_spaces_input(char *str);
char	*extract_key_name(char *str, int start);
char	*get_value_by_key(t_env *full_env, char *key);//doit pas etre la
char	*expand_string(char *str, t_env *env);
/*parsing/handle_quotes.c*/
char	*delete_quote(char *input);
void	inverse_string(char *str, int flag);
/*parsing/parse.c*/
int		is_same_string(char *str1, char *str2);
/*parsing/syntax_error.c*/
int		check_alone_quote(char *str);
int		check_pipes(char *str);
int		valid_rafters(char *str, int len);
int		check_rafters(char *str);
int		check_empty(char *str);
int		syntax_error(t_all *all, char *input);
/*parsing/utils_parsing.c*/
int		iswhitespace(const char c);
int		is_space(char c);
int		is_meta(char c);
int		is_quote(char c);
int		count_meta(char *input);
int		count_quote(char *input);
int		ft_strcmp(const char *s1, const char *s2);

/*t_env/*/

/*t_env/t_env_init.c*/
char	*get_env_name(char *env_line);
char	*get_env_value(char *env_line, char *name);
void	init_env(t_all *data, char **env);//surveiller si ca ca fait pas de dingz
void	free_t_env(t_env **env);
t_env	*t_env_new(char	*name, char *value, int display);
/*t_env/t_env_operation.c*/
t_env	*get_last_t_env(t_env *env);
void	print_t_env(t_env *env);//kick ?
void	add_t_env(t_env **env, char *name, char *value, int display);
char	*get_key(t_env *full_env, char *key);


#endif