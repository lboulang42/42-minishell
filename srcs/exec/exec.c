/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:31:02 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/17 18:29:27 by gcozigon         ###   ########.fr       */
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
	if (cmd_path[ft_strlen(cmd_path) - 1] == '/')
	{
		ft_printf("Pipex: %s: %s\n", cmd_path, ERR_NOTDIR);
		free(cmd_path);
		return ;
	}
	if (access(cmd_path, F_OK))
		ft_printf("Pipex: %s: '%s'\n", cmd_name, ERR_CMD);
	else if (access(cmd_path, X_OK))
		ft_printf("Pipex: %s: %s\n", cmd_path, ERR_PERM);
	free(cmd_path);
}

void	exec_init(t_all *all, char *input)
{
	char	**lines;//lines = inputs splités aux |
	int     lines_number;
	int		i;

	i = -1;
	lines = ft_split(input, '|');//gerer si cmd vide plus tard
	lines_number = ft_tab_len(lines);
	while (lines[++i])
		handle_line(all, lines[i], lines_number, i);
	for (int j = 0; j < lines_number; j++)
		waitpid(all->pid[j], NULL, 0);
	signal(SIGINT, & ctrlc);
	close(all->link_fd[0]);
	ft_free_tab((void **)lines);
}

/*
separate way if cmd is global path / only name / only name without PATH in env
*/
char	*ft_check_acces(char **env_path, char *cmd_name, int i)
{
	char	*cmd_path;
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

void    handle_line(t_all *all, char *line, int total_pipes, int index_pipe)//tokenisation de con
{
	char    **tokens;
	char *cmd_path;

	pipe(all->link_fd);
	signal(SIGINT, SIG_IGN);
	tokens = ft_split(line, ' ');

	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
	{
		signal(SIGINT, & ctrlc);
		signal(SIGQUIT, & ctrld);
		get_outfile_infile(all, tokens);//redirige les infiles/outfiles de la line;
		tokens = kick_empty_tokens(tokens);//vire les bails vide
		tokens_positif(tokens);//repasse tout en positif
		cmd_path = get_path_putain(tokens[0], all->env);
		if (index_pipe != 0)
		{
			dup2(all->prev, 0);
			close(all->prev);
		}
		if (index_pipe != total_pipes - 1)
		{
			dup2(all->link_fd[1], 1);
		}	
		close(all->link_fd[0]);
		close(all->link_fd[1]);
		if (cmd_path && tokens)
			execve(cmd_path, tokens, all->default_env);
		exit(127);
	}
	else
	{
		close(all->link_fd[1]);
		if (all->prev > 0)
			close(all->prev);
		all->prev = all->link_fd[0];
	}
	ft_free_tab((void **)tokens);
}

char *get_path_putain(char *cmd, t_env *env)
{
	char *PATH;
	char **spl_path;
	char *cmd_path;
	PATH = get_key(env, "PATH");//ca ca merde
	spl_path = ft_split(PATH, ':');//ca ca merde
	cmd_path = ft_check_acces(spl_path, cmd, -1);
	return (cmd_path);
}
