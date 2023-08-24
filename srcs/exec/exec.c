/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:31:02 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/24 13:40:45 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_access_fail(char *cmd_path, char *cmd_name)
{
	if (!cmd_path)
	{
		fprintf(stderr, "Minishell:%s:%s\n", ERR_CMD, cmd_name);
		// printf("Minishell :%s:%s\n", ERR_CMD, cmd_name);
		return ;
	}
	if (cmd_path[ft_strlen(cmd_path) - 1] == '/')
	{
		fprintf(stderr, "Minishell: %s: %s\n", cmd_path, ERR_NOTDIR);
		// ft_printf("Pipex: %s: %s\n", cmd_path, ERR_NOTDIR);
		free(cmd_path);
		return ;
	}
	if (access(cmd_path, F_OK))
	{
		fprintf(stderr, "Minishell: %s: %s\n", cmd_name, ERR_CMD);
		// ft_printf("Pipex: %s: '%s'\n", cmd_name, ERR_CMD);
	}
	else if (access(cmd_path, X_OK))
	{
		fprintf(stderr, "Minishell: %s: %s\n", cmd_path, ERR_PERM);
		// ft_printf("Pipex: %s: %s\n", cmd_path, ERR_PERM);
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
	
	i = -1;
	all->all_lines = NULL;
	all->all_lines = ft_split(input, '|');//gerer si cmd vide plus tard
	free(input);
	lines_number = ft_tab_len(all->all_lines);
	all->prev = -1;
	all->btn_fd = -1;
	while (all->all_lines[++i])
		handle_line(all, all->all_lines, i);
	for (int j = 0; j < lines_number; j++)
	{
		if (all->pid[j] >= 0)
		{
			waitpid(all->pid[j], &wstatus, 0);
			if (WIFEXITED(wstatus))
			{
				tmp = ft_itoa(WEXITSTATUS(wstatus))	;
				do_export(all, "?", tmp);
				free(tmp);
			}
		}
	}
	if (all->prev > 0)
		close(all->prev);
	signal(SIGINT, & ctrlc);
	ft_free_tab((void **)all->all_lines);
}

/*
separate way if cmd is global path / only name / only name without PATH in env
*/
char	*ft_check_acces(char **env_path, char *cmd_name, int i)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (ft_strchr(cmd_name, '/'))
	{
		cmd_path = ft_strdup(cmd_name);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		return (ft_access_fail(cmd_path, cmd_name), NULL);
	}
	while (env_path && env_path[++i])
	{
		cmd_path = ft_join_path(env_path[i], cmd_name);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		if (env_path[i + 1])
			free(cmd_path);
	}
	return (ft_access_fail(cmd_path, cmd_name), NULL);
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

void    handle_line(t_all *all, char **all_lines, int index_pipe)//tokenisation de con
{
	char    **tokens;
	char *cmd_path;
	int	builtin_code;
	int btn_fd;
	int default_out;
	
	pipe(all->link_fd);
	signal(SIGINT, SIG_IGN);
	all->tokens = ft_split(all_lines[index_pipe], ' ');
	if (!all->tokens)
		return;
	builtin_code = is_builtin(all->tokens[0]);
	if (builtin_code >= 0 && ft_tab_len(all_lines) == 1)
	{
		all->pid[index_pipe] = -1;
		default_out = dup(1);
		btn_fd = get_outfile_infile_builtin(all, all->tokens, all_lines);
		if (btn_fd == -2)
		{
			ft_free_tab((void **)all->tokens);
			do_export(all, "?", "1");
			return ;
		}
		all->tokens = kick_empty_tokens(all->tokens);
		tokens_positif(all->tokens);
		int status = execute_builtin(all->tokens, all, builtin_code, all_lines);
		ft_free_tab((void **)all->tokens);
		close(all->link_fd[0]);
		close(all->link_fd[1]);
		dup2(default_out, 1);
		close(default_out);
		char *atoi;
		atoi = ft_itoa(status);
		do_export(all, "?", atoi);
		free(atoi);
		//status code
		return ;
	}
	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
	{

		signal(SIGINT, & ctrlc);
		signal(SIGQUIT, & reactiv);
		get_outfile_infile(all, all->tokens, all_lines);//redirige les infiles/outfiles de la line;
		all->tokens = kick_empty_tokens(all->tokens);//vire les bails vide
		tokens_positif(all->tokens);//repasse tout en positif
		if (builtin_code >= 0)
		{
			plug_builtin(all->tokens, all, builtin_code, all_lines, index_pipe);
			execute_builtin(all->tokens, all, builtin_code, all_lines);
			free_t_env(&all->env);
			ft_free_tab((void **)all->tokens);
			ft_free_tab((void **)all_lines);
			exit(0);
		}
		redirection_execve(all, all_lines, index_pipe);
		cmd_path = get_path_putain(all->tokens[0], all->env);
		char **env = get_env(all->env);//faut test avec export
		if (cmd_path && all->tokens)
			execve(cmd_path, all->tokens, env);
		ft_free_tab((void **)env);
		free_t_env(&all->env);
		ft_free_tab((void **)all->tokens);
		ft_free_tab((void **)all_lines);
		// if (!cmd_path)
		// 	exit (126);
		exit(127);
	}
	else
	{
		close(all->link_fd[1]);
		if (all->prev > 0)
			close(all->prev);
		all->prev = all->link_fd[0];
		signal(SIGQUIT, SIG_IGN);
	}
	if (all->link_fd[1] > 0)
		close(all->link_fd[1]);
	ft_free_tab((void **)all->tokens);
}



char *get_path_putain(char *cmd, t_env *env)
{
	char *PATH;
	char **spl_path;
	char *cmd_path;
	
	PATH = get_key(env, "PATH");//ca ca merde
	if (!PATH)
	{
		cmd_path = ft_check_acces(NULL, cmd, -1);
		return (cmd_path);	
	}
	spl_path = ft_split(PATH, ':');//ca ca merde
	cmd_path = ft_check_acces(spl_path, cmd, -1);
	free(PATH);
	ft_free_tab((void **)spl_path);
	return (cmd_path);
}
