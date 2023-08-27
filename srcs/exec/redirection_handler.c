/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:33:35 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/27 17:42:30 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_infile(t_all *all, int index_name)
{
	int	fd;

	fd = open(all->tokens[index_name], O_RDONLY);
	return (fd);
}

void ft_free_heredoc(t_all *all)
{
	if (all->here_doc_readline)
			free(all->here_doc_readline);
	close(all->here_doc_fd[1]);
	close(all->here_doc_fd[0]);
	safeclose(all->link_fd[0]);
	safeclose(all->link_fd[1]);
	safeclose(all->default_out);
	free_t_env(&all->env);
	ft_free_tab((void **)all->tokens);
	ft_free_tab((void **)all->all_lines);
	free(all->here_doc_limiter);
}

int	handle_heredoc(t_all *all, int index_name)
{
	int	wstatus;
	int	pid;

	all->here_doc_limiter = ft_strdup(all->tokens[index_name]);
	pipe(all->here_doc_fd);
	pid = fork();
	if (pid == -1)
		return (close(all->here_doc_fd[0]), close(all->here_doc_fd[1]), -1);
	if (pid == 0)
	{
		signal(SIGINT, &ctrldhere_doc);
		while (1)
		{
			all->here_doc_readline = readline("minishell here_doc >>");
			if (!all->here_doc_readline)
				break ;
			
			if (is_same_string(all->here_doc_readline, all->here_doc_limiter))
				break ;
			all->here_doc_readline = expand_string(all->here_doc_readline, all->env);
			ft_putstr_fd(all->here_doc_readline, all->here_doc_fd[1]);
			ft_putstr_fd("\n", all->here_doc_fd[1]);
			free(all->here_doc_readline);
		}
		ft_free_heredoc(all);
		exit(1);
	}
	free(all->here_doc_limiter);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		update_status_int(all, WEXITSTATUS(wstatus));
	close(all->here_doc_fd[1]);
	signal(SIGINT, SIG_IGN);
	return (all->here_doc_fd[0]);
}

int	handle_outfile_trunc(t_all *all, int index_name)
{
	int	fd;

	fd = open(all->tokens[index_name], O_RDWR | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

int	handle_outfile_append(t_all *all, int index_name)
{
	int	fd;

	fd = open(all->tokens[index_name], O_RDWR | O_CREAT | O_APPEND, 0666);
	return (fd);
}

/*
redirection builtin
return -2 si error a l'ouverture d'un file descriptor
*/
int	get_outfile_infile_builtin(t_all *all, char **tokens, char **all_lines)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (tokens[++i +1])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, i +1);
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, i +1);
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, i +1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, i +1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			if (fd == -1)
			{
				if (errno == 13)
					fprintf(stderr, "Minishell: %s: %s\n", tokens[i +1], ERR_PERM);
				else
					fprintf(stderr, "Minishell :%s: %s\n", tokens[i +1], ERR_NOSUCHF);
				return (-2);
			}
			if (is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
			{
				dup2(fd, 1);
			}
			if (all->prev > 0)
				close(all->prev);
			close(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
		}
	}
	return (fd);
}

//redirection command
void	get_outfile_infile(t_all *all, char **tokens, char **all_lines, int index_pipe)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (tokens[++i +1])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, i +1);
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, i +1);
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, i +1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, i +1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			if (fd == -1)
			{
				fprintf(stderr, "Minishell: %s: %s\n", tokens[i+1], strerror(errno));
				free_t_env(&all->env);
				ft_free_tab((void **)all_lines);
				ft_free_tab((void **)tokens);
				exit (1);
			}
			if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<"))
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
		}
	}
}
