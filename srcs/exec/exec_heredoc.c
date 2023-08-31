/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:22:09 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:18:09 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_heredoc(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->nbr_redir)
	{
		if (all->redir_list[i].type == 4)
		{
			all->redir_list[i].here_doc_fd = handle_heredoc2(all,
					all->redir_list[i].file);
		}
	}
}

int	handle_heredocbooste(t_all *all)
{
	int	index;

	index = all->index_redir + all->redir_before;
	return (all->redir_list[index].here_doc_fd);
}

int	handle_heredoc2(t_all *all, char *limiter)
{
	int	pid;
	int	wstatus;

	all->here_doc_limiter = ft_strdup(limiter);
	pipe(all->here_doc_fd);
	pid = fork();
	if (pid == -1)
		return (safeclose(all->here_doc_fd[0]), safeclose(all->here_doc_fd[1]),
			-1);
	if (pid == 0)
		child_heredoc2(all);
	free(all->here_doc_limiter);
	waitpid(pid, &wstatus, 0);
	safeclose(all->here_doc_fd[1]);
	signal(SIGINT, SIG_IGN);
	return (all->here_doc_fd[0]);
}

void	child_heredoc2(t_all *all)
{
	signal(SIGINT, &ctrlchere_doc);
	while (1)
	{
		all->here_doc_readline = readline("minishell heredoc >>");
		if (!all->here_doc_readline)
			break ;
		if (is_same_string(all->here_doc_readline, all->here_doc_limiter))
			break ;
		all->here_doc_readline = expand_string(all->here_doc_readline,
				all->env);
		ft_putendl_fd(all->here_doc_readline, all->here_doc_fd[1]);
		free(all->here_doc_readline);
	}
	ft_free_heredoc2(all);
	exit(1);
}

void	ft_free_heredoc2(t_all *all)
{
	if (all->here_doc_readline)
		free(all->here_doc_readline);
	safeclose(all->here_doc_fd[1]);
	safeclose(all->here_doc_fd[0]);
	free_t_env(&all->env);
	if (all->here_doc_limiter)
		free(all->here_doc_limiter);
	free_redir_list(all);
	free(all->input);
}
