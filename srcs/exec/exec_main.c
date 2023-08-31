/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:31:02 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 15:59:23 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_init(t_all *all)
{
	all->index_redir = 0;
	all->status = 0;
	all->prev_fd = -1;
	all->link_fd[0] = -1;
	all->link_fd[1] = -1;
	all->redir_before = 0;
	all->all_lines = ft_split(all->input, '|');
	if (!all->all_lines)
		return ((void)free(all->input), 0);
	free(all->input);
	return (1);
}

void	start_exec(t_all *all)
{
	int		i;
	int		j;

	i = -1;
	if (!exec_init(all))
		return ;
	while (all->all_lines[++i])
		handle_line(all, i);
	j = 0;
	while (j < ft_tab_len(all->all_lines))
	{
		waitpid(all->pid[j], &all->status, 0);
		if (WIFEXITED(all->status))
		{
			all->status = WEXITSTATUS(all->status);
			update_status_int(all, all->status);
		}
		j++;
	}
	if (all->prev_fd > 0)
		safeclose(all->prev_fd);
	signal(SIGINT, &ctrlc);
	ft_free_tab((void **)all->all_lines);
	free_redir_list(all);
}

void	parent(t_all *all)
{
	safeclose(all->link_fd[1]);
	if (all->prev_fd > 0)
		safeclose(all->prev_fd);
	all->prev_fd = all->link_fd[0];
	signal(SIGQUIT, SIG_IGN);
	if (all->link_fd[1] > 0)
		safeclose(all->link_fd[1]);
	ft_free_tab((void **)all->tokens);
	ft_free_tab_size((void **)all->arg, all->args_size + 1);
}

void	handle_line(t_all *all, int index_pipe)
{
	int		builtin_code;

	all->pid[index_pipe] = -1;
	all->default_out_fd = -1;
	signal(SIGINT, SIG_IGN);
	all->tokens = ft_split(all->all_lines[index_pipe], ' ');
	if (!all->tokens)
		return ;
	if (!parse(all, all->tokens))
		return ;
	builtin_code = is_builtin(all->cmd);
	if (builtin_code >= 0 && ft_tab_len(all->all_lines) == 1)
		return ((void)only_builtin(all, index_pipe, builtin_code));
	pipe(all->link_fd);
	all->pid[index_pipe] = fork();
	if (all->pid[index_pipe] == 0)
		child(all, index_pipe, builtin_code);
	else
	{
		all->redir_before += count_redir(all->tokens);
		parent(all);
	}
}
