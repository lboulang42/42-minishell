/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:31:02 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/27 15:03:28 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
char	*ft_join_path(char *try_path, char *cmd_name)
{
	char	*tmp_path;
	char	*cmd_path;

	tmp_path = ft_strjoin(try_path, "/");
	if (!tmp_path)
		return (NULL);
	cmd_path = ft_strjoin(tmp_path, cmd_name);
	if (!cmd_path)
		return (free(tmp_path), NULL);
	free(tmp_path);
	return (cmd_path);
}

int is_this_meta(char *s, char *metachar)
{
	int i;

	i = -1;
	if (ft_strlen(s) != ft_strlen(metachar))
		return (0);
	while (s[++i])
		if (s[i] != metachar[i])
			return (0);
	return (1);
}

int find(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

/*ft_access_fail renvoie un message d'erreur similaire a celui de bash dans le cas ou la commande ne peut pas être executée*/
/*
En cas d'erreur access return -1;
Si F_OK fail :
	-Ne peut pas accéder au fichier parcequ'il n'existe pas.
	- si '/' dans le nom du fichier : No such file or directory
	- si pas de '/' dans le nom du fichier : command not found;
	- Error code : 127 (sera set par défaut dans ft_child());
Si X_OK fail :
	- Ne peut pas accéder au fichier (plusieurs raisons différentes, on set l'error code avec strerror)
	- Error code : 126 (via ft_kill_dir)
*/
void	ft_access_fail(char **PATHvaaaar, char *cmd_path, char *cmd_name)
{
	char *tmp;

	if (cmd_path)
	{
		if (access(cmd_path, F_OK))
		{
			if (!find(cmd_name, '/'))
				fprintf(stderr, "mini :%s : %s\n", cmd_name, "command not found");
			else
				fprintf(stderr, "mini :%s : %s\n", cmd_name, "No such file or directory");
		}
		else if (access(cmd_path, X_OK))
		{
			fprintf(stderr, "minishell : %s: %s\n",cmd_name,  strerror(errno));
			ft_kill_dir(PATHvaaaar, cmd_path, cmd_name);
		}
	}
	if (cmd_path)
		free(cmd_path);
}

void	exec_init(t_all *all, char *input)
{
	char	**lines;//lines = inputs splités aux |
	int     lines_number;
	int		i;
	int wstatus;
	char *tmp;
	int j;
	i = -1;
	all->all_lines = NULL;
	all->all_lines = ft_split(input, '|');//gerer si cmd vide plus tard
	if (!all->all_lines)
		return ((void)free(input));
	free(input);
	lines_number = ft_tab_len(all->all_lines);
	all->prev = -1;
	all->btn_fd = -1;
	while (all->all_lines[++i])
		handle_line(all, all->all_lines, i);
	
	j = 0;
	while (j < lines_number)
	{
		if (all->pid[j] >= 0)
		{
			waitpid(all->pid[j], &wstatus, 0);
			if (WIFEXITED(wstatus))
				update_status_int(all, WEXITSTATUS(wstatus));
		}
		j++;
	}
	if (all->prev > 0)
		close(all->prev);
	signal(SIGINT, & ctrlc);
	ft_free_tab((void **)all->all_lines);
}

void ft_kill_dir(char **PATHvar, char *cmd_path, char *cmd_name)
{
	t_all *all;

	all = init_data();

	if (cmd_path)
		free(cmd_path);

	ft_free_tab((void **)all->tokens);
	free_t_env(&all->env);
	ft_free_tab((void **)PATHvar);
	ft_free_tab((void **)all->all_lines);
	exit(126);
}
/*
separate way if cmd is global path / only name / only name without PATH in env
*/
char	*ft_check_acces(char **env_path, char *cmd_name, int i)
{
	char	*cmd_path;
	struct stat tmp;

	cmd_path = NULL;
	if (ft_strchr(cmd_name, '/'))
	{
		cmd_path = ft_strdup(cmd_name);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			stat(cmd_path, &tmp);
			if (!S_ISREG(tmp.st_mode))
			{
				fprintf(stderr, "minishell : %s : %s", cmd_name, "Is a directory");
				ft_kill_dir(env_path, cmd_path, cmd_name);
			}
			return (cmd_path);
		}
		return (ft_access_fail(env_path, cmd_path, cmd_name), NULL);
	}
	while (env_path && env_path[++i])
	{
		cmd_path = ft_join_path(env_path[i], cmd_name);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			stat(cmd_path, &tmp);
			if (!S_ISREG(tmp.st_mode))
			{
				fprintf(stderr, "minishell : %s : %s", cmd_name, "Is a directory");
				ft_kill_dir(env_path, cmd_path, cmd_name);
			}
			return (cmd_path);
		}
		if (env_path[i + 1])
			free(cmd_path);
	}
	return (ft_access_fail(env_path, cmd_path, cmd_name), NULL);
}

char **get_env(t_env *env)
{
	t_env *tmp;
	char **res = NULL;
	char *temp2;
	
	int counter = 0;
	tmp = env;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (counter+1));
	tmp = env;
	counter = 0;
	while (tmp)
	{
			temp2 = ft_strjoin(tmp->name, (char *)"=");
			res[counter] = ft_strjoin(temp2, tmp->value);
			free(temp2);
			tmp = tmp->next;
			counter++;
	}
	res[counter] = NULL;
	return (res);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void redirection_execve(t_all *all, char **all_lines, int index_pipe)
{
	if (index_pipe != 0)
	{
		dup2(all->prev, 0);
		close(all->prev);
	}
	if (index_pipe != ft_tab_len(all_lines) - 1)
	{
		dup2(all->link_fd[1], 1);
	}
	close(all->link_fd[0]);
	close(all->link_fd[1]);
}

void plug_builtin(char **tokens, t_all *all, int i, char **all_lines, int index_pipe)
{
	if (index_pipe != ft_tab_len(all_lines) -1)
	{
		dup2(all->link_fd[1], 1);
	}
	if (index_pipe != 0)
	{
		dup2(all->prev, 0);
		ft_close(all->prev);
	}
	ft_close(all->link_fd[0]);
	ft_close(all->link_fd[1]);
}

/*
premier token peut etre une redir
*/

void ft_free_child(t_all *all, char **env_array, char *cmd_path)
{
	free_t_env(&all->env);
	ft_free_tab((void **)env_array);
	ft_free_tab((void **)all->tokens);
	ft_free_tab((void **)all->all_lines);
	if (cmd_path)
		free(cmd_path);
}


void child(t_all *all, int index_pipe, int builtin_code)
{
	char	*cmd_path;
	char	**env;

	signal(SIGINT, & ctrlc);
	tokens_positif(all->tokens);
	redirection_execve(all, all->all_lines, index_pipe);
	get_outfile_infile(all, all->tokens, all->all_lines, index_pipe);
	all->tokens = kick_empty_tokens(all->tokens);
	if (builtin_code >= 0)
	{
		int status = execute_builtin(all->tokens, all, builtin_code, all->all_lines);
		free_t_env(&all->env);
		ft_free_tab((void **)all->tokens);
		ft_free_tab((void **)all->all_lines);
		exit(status);
	}
	cmd_path = get_path_putain(all->tokens[0], all->env);
	env = get_env(all->env);
	if (cmd_path && all->tokens)
		execve(cmd_path, all->tokens, env);
	ft_free_child(all, env, cmd_path);
	exit(127);
}

void parent(t_all *all)
{
	close(all->link_fd[1]);
	if (all->prev > 0)
		close(all->prev);
	all->prev = all->link_fd[0];
	signal(SIGQUIT, SIG_IGN);
	if (all->link_fd[1] > 0)
		close(all->link_fd[1]);
	ft_free_tab((void **)all->tokens);
}

void update_status_int(t_all *all, int status)
{
	char *itoa_status;
	itoa_status = ft_itoa(status);
	do_export(all, "?", itoa_status);
	free(itoa_status);
}

void only_builtin(t_all *all, int index_pipe, int builtin_code)
{
	int btn_fd;
	
	all->pid[index_pipe] = -1;
	all->default_out = dup(1);
	tokens_positif(all->tokens);
	btn_fd = get_outfile_infile_builtin(all, all->tokens, all->all_lines);
	if (btn_fd == -2)
	{
		ft_free_tab((void **)all->tokens);
		do_export(all, "?", "1");
		dup2(all->default_out, 1);
		close(all->default_out);
		return ;
	}
	all->tokens = kick_empty_tokens(all->tokens);
	int status = execute_builtin(all->tokens, all, builtin_code, all->all_lines);
	ft_free_tab((void **)all->tokens);
	dup2(all->default_out, 1);
	close(all->default_out);
	update_status_int(all, status);
}
void    handle_line(t_all *all, char **all_lines, int index_pipe)//tokenisation de con
{
	char    **tokens;
	char *cmd_path;
	int	builtin_code;
	
	signal(SIGINT, SIG_IGN);
	all->tokens = ft_split(all_lines[index_pipe], ' ');
	if (!all->tokens)
		return;
	builtin_code = is_builtin(all->tokens[0]);
	if (builtin_code >= 0 && ft_tab_len(all_lines) == 1)
		return ((void)only_builtin(all, index_pipe, builtin_code));
	pipe(all->link_fd);
	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
		child(all, index_pipe, builtin_code);
	else
		parent(all);
}


char *get_path_putain(char *cmd, t_env *env)
{
	char *PATH;
	char **spl_path;
	char *cmd_path;
	
	PATH = get_key(env, "PATH");
	if (!PATH)
	{
		cmd_path = ft_check_acces(NULL, cmd, -1);
		return (cmd_path);	
	}
	spl_path = ft_split(PATH, ':');//ca ca merde
	free(PATH);
	cmd_path = ft_check_acces(spl_path, cmd, -1);
	ft_free_tab((void **)spl_path);
	return (cmd_path);
}
