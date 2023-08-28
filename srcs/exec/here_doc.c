/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:46:20 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 21:24:24 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_heredoc(t_all *all)
{
	if (all->here_doc_readline)
		free(all->here_doc_readline);
	safeclose(all->here_doc_fd[1]);
	safeclose(all->here_doc_fd[0]);
	safeclose(all->link_fd[0]);
	safeclose(all->link_fd[1]);
	safeclose(all->default_out);
	free_t_env(&all->env);
	ft_free_tab((void **)all->tokens);
	ft_free_tab((void **)all->all_lines);
	ft_free_tab((void **)all->arg);
	free(all->here_doc_limiter);
}

void wait_and_update(t_all *all, int pid)
{
	int wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		update_status_int(all, WEXITSTATUS(wstatus));
}

void	child_heredoc(t_all *all)
{
	signal(SIGINT, &ctrlchere_doc);
	while (1)
	{
		all->here_doc_readline = readline("minishell here_doc >>");
		if (!all->here_doc_readline)
			break ;
		if (is_same_string(all->here_doc_readline, all->here_doc_limiter))
			break ;
		all->here_doc_readline = expand_string(all->here_doc_readline, all->env);
		ft_putendl_fd(all->here_doc_readline, all->here_doc_fd[1]);
		free(all->here_doc_readline);
	}
	ft_free_heredoc(all);
	exit(1);
}

int	handle_heredoc(t_all *all, int index_name)
{
	int	pid;

	all->here_doc_limiter = ft_strdup(all->tokens[index_name]);
	pipe(all->here_doc_fd);
	pid = fork();
	if (pid == -1)
		return (safeclose(all->here_doc_fd[0]), safeclose(all->here_doc_fd[1]), -1);
	if (pid == 0)
		child_heredoc(all);
	free(all->here_doc_limiter);
	// wait_and_update(all, pid);
	wait(NULL);
	safeclose(all->here_doc_fd[1]);
	signal(SIGINT, SIG_IGN);
	return (all->here_doc_fd[0]);
}
