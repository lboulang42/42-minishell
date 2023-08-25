/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:33:35 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/25 22:52:08 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_infile(t_all *all, char **tokens_array, int index_name)
{
	int fd;
	
	fd = open(tokens_array[index_name], O_RDONLY);
	return (fd);
}

int handle_heredoc(t_all *all, char **tokens_array, int index_name, char **all_lines)//peut leak si ctrl+d pendant le heredoc
{
	// all->here_doc_buffer = NULL;
	// all->here_doc_line = NULL;
	all->here_doc_limiter = ft_strdup(tokens_array[index_name]);
	// static char *stat_buff;
	
	pipe(all->here_doc_fd);
	// signal(SIGINT, SIG_IGN);
	int pid = fork();
	if (pid == -1)
		return (close(all->here_doc_fd[0]), close(all->here_doc_fd[1]), -1);
	if (pid == 0)
	{
		
		signal(SIGINT, &ctrldhere_doc);
		while (1)
		{
			all->here_doc_readline = readline("minishell here_doc >>");
			if (is_same_string(all->here_doc_readline, all->here_doc_limiter))
				break;
			all->here_doc_readline = expand_string(all->here_doc_readline, all->env);
			ft_putstr_fd(all->here_doc_readline, all->here_doc_fd[1]);
			ft_putstr_fd("\n", all->here_doc_fd[1]);
			free(all->here_doc_readline);
		}
		if (all->here_doc_readline)
			free(all->here_doc_readline);
		close(all->here_doc_fd[1]);
		close(all->here_doc_fd[0]);
		close(all->link_fd[0]);
		close(all->link_fd[1]);
		free_t_env(&all->env);
		ft_free_tab((void **)tokens_array);
		ft_free_tab((void **)all_lines);
		free(all->here_doc_limiter);
		exit(1);
	}
	free(all->here_doc_limiter);
	waitpid(pid, NULL, 0);
	/*
	wait le pid pour mettre a jour le signal
	*/
	close(all->here_doc_fd[1]);
	signal(SIGINT, SIG_IGN);
	return (all->here_doc_fd[0]);
}

int handle_outfile_trunc(t_all *all, char **tokens_array, int index_name)
{
	int fd;

	fd = open(tokens_array[index_name], O_RDWR | O_CREAT| O_TRUNC, 0666);

	return (fd);
}
int handle_outfile_append(t_all *all, char **tokens_array, int index_name)
{
	int fd;
	
	fd = open(tokens_array[index_name], O_RDWR | O_CREAT| O_APPEND, 0666);
	return (fd);
}

int	get_outfile_infile_builtin(t_all *all, char **tokens, char **all_lines)
{
	int	i;

	i = -1;
	int fd = -1;
	while (tokens[++i +1])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, tokens, i+1);//infile name = i+1
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, tokens, i+1, all_lines);//i+1 = limiter du here_doc
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, tokens, i+1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, tokens, i+1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			if (fd == -1)
			{
				if (errno == 13)
					fprintf(stderr, "Minishell: %s: %s\n", tokens[i+1], ERR_PERM);
				else
					fprintf(stderr, "Minishell :%s: %s\n", tokens[i+1], ERR_NOSUCHF);
				close(all->link_fd[1]);
				close(all->link_fd[0]);
				return (-2);
			}
			
			if (is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
			{
				dup2(fd, 1);
				// dup2(fd, 0);
			}
			// else
			// {
				// dup2(fd, 1);
			// }
			close(all->link_fd[0]);
			close(all->link_fd[1]);
			if (all->prev > 0)
				close(all->prev);
			close(fd);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
			// return (fd);
		}
	}
	return (fd);
}

/*
if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<"))
			{
				// fprintf(stderr, "REDIRECT ENTREE\n");
				dup2(fd, 0);
				if (index_pipe != ft_tab_len(all_lines) - 1)
				{
					dup2(all->link_fd[1], 1);
				}
			}
			else
			{
				// fprintf(stderr, "REDIRECT SORTIE\n");
				dup2(fd, 1);
				if (index_pipe != 0)
				{
					dup2(all->prev, 0);
					close(all->prev);
				}
			}
			close(fd);
			close(all->link_fd[0]);
			close(all->prev);
			close(all->link_fd[1]);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
			

*/
void	get_outfile_infile(t_all *all, char **tokens, char **all_lines, int index_pipe)
{
	int	i;

	i = -1;
	int fd = -1;
	while (tokens[++i +1])
	{
		if (is_this_meta(tokens[i], "<"))
			fd = handle_infile(all, tokens, i+1);//infile name = i+1
		else if (is_this_meta(tokens[i], "<<"))
			fd = handle_heredoc(all, tokens, i+1, all_lines);//i+1 = limiter du here_doc
		else if (is_this_meta(tokens[i], ">"))
			fd = handle_outfile_trunc(all, tokens, i+1);
		else if (is_this_meta(tokens[i], ">>"))
			fd = handle_outfile_append(all, tokens, i+1);
		if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<") || is_this_meta(tokens[i], ">") || is_this_meta(tokens[i], ">>"))
		{
			// fprintf(stderr, "entré ici\n");
			if (fd == -1)
			{
				if (errno ==13)
					fprintf(stderr, "Minishell: %s: %s\n", tokens[i+1], ERR_PERM);
				else
					fprintf(stderr, "Minishell :%s: %s\n", tokens[i+1], ERR_NOSUCHF);
				free_t_env(&all->env);
				ft_free_tab((void **)all_lines);
				ft_free_tab((void **)tokens);
				close(all->link_fd[0]);
				close(all->link_fd[1]);
				exit (1);
			}
			if (is_this_meta(tokens[i], "<") || is_this_meta(tokens[i], "<<"))
			{
				// fprintf(stderr, "REDIRECT ENTREE\n");
				dup2(fd, 0);
				if (index_pipe != ft_tab_len(all_lines) - 1)
				{
					dup2(all->link_fd[1], 1);
				}
			}
			else
			{
				// fprintf(stderr, "REDIRECT SORTIE\n");
				dup2(fd, 1);
				if (index_pipe != 0)
				{
					dup2(all->prev, 0);
					close(all->prev);
				}
			}
			close(fd);
			close(all->link_fd[0]);
			close(all->prev);
			close(all->link_fd[1]);
			tokens[i][0] = '\0';
			tokens[i + 1][0] = '\0';
		}
	}
}
	