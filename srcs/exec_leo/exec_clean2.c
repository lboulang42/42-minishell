/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:14:59 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/04 20:06:34 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	if (fd3 > -1)
		close(fd2);
	if (fd4 > -1)
		close(fd2);
}

void	get_outfile_infile(t_all *all, char **tokens)
{
	int	i;

	i = -1;
	int fd = -1;
	while (tokens[++i +1])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, tokens, i+1);//infile name = i+1
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, tokens, i+1);//i+1 = limiter du here_doc
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, tokens, i+1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, tokens, i+1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			if (fd == -1)
			{
				fprintf(stderr, "%s: ERRORRRRR\n", tokens[i + 1]);
				exit(1);
			}
			if ((is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<")))
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
		}
	}
}

char **get_tokens(t_all *all, char *line)
{
	char **tokens;
	tokens = ft_split(line, ' ');//if fail ??
	if (!tokens)
		fprintf(stderr, "tokens split failed (get tokens)");
	get_outfile_infile(all, tokens);
	tokens = kick_empty(tokens);//fonction de merde gpt; peut fail
	tokens_positif(tokens);
	return (tokens);
}

char **get_path(t_all *all, char *cmd)
{
	char	**split_path;
	char	*env_path;
	char	*cmd_path;

	env_path = get_value_by_key(all->env, "PATH");//can fail
	if (!env_path)
		fprintf(stderr, "env_path get value by key failed");
	
	split_path = ft_split(env_path, ':');//can fail
	if (!split_path)
		fprintf(stderr, "env_path get value by key failed");
	
	cmd_path = ft_check_acces(split_path, cmd, -1);
	free(env_path);
	ft_free_tab((void **)split_path);
	return (cmd_path);
}

void	dup_close(int fd, int fd_dup2)
{
	dup2(fd, fd_dup2);
	close(fd);
}

void    handle_line(t_all *all, char *line, int number_of_pipes, int index_pipe)
{
	char	**tokens;
	char	*cmd_path;

	pipe(all->link_fd);
	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
	{
		tokens = get_tokens(all, line);
		cmd_path = get_path(all, tokens[0]);
		if (index_pipe != 0)
			dup_close(all->prev, 0);
		if (index_pipe != number_of_pipes - 1)
			dup2(all->link_fd[1], 1);
		ft_close_fd(all->link_fd[0], all->link_fd[1], -1, -1);
		if (cmd_path && tokens)
			execve(cmd_path, tokens, all->default_env);//faut passer le t_env env char **
		exit(127);
	}
	else	{
		close(all->link_fd[1]);
		if (all->prev > 0)
			close(all->prev);
		all->prev = all->link_fd[0];
	}
	ft_free_tab((void **)tokens);
}

void	exec_init(t_all *all, char *input)
{
	char	**lines;
	int		number_of_pipes;
	int		i;

	i = -1;
	lines = ft_split(input, '|');//test si fail
	if (!lines)
		fprintf(stderr, "lines split failed (exec_init)");
	number_of_pipes = ft_tab_len(lines);
	while (lines[++i])
		handle_line(all, lines[i], number_of_pipes, i);

	ft_wait_pid(all, number_of_pipes);
	
	close(all->link_fd[0]);
	ft_free_tab((void **)lines);
}