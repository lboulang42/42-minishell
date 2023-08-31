/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:28:12 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:06:40 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Return -1 si la cmd_name != nom de builtin, sinon return builtin_code;
*/
int	is_builtin(char *cmd_name)
{
	int			i;
	static char	*bltnnames[7] = {
		"cd", "echo", "exit", "export", "pwd", "unset", "env"
	};

	i = -1;
	while (++i < 7)
		if (is_same_string(cmd_name, bltnnames[i]))
			return (i);
	return (-1);
}

/*
execute le bon builtin
*/
int	execute_builtin(t_all *all, int builtin_code)
{
	if (builtin_code == 0)
		return (cd(all, all->tokens));
	else if (builtin_code == 1)
		return (echo(all->tokens));
	else if (builtin_code == 2)
		return (ft_exit(all), 1);
	else if (builtin_code == 3)
		return (export(all));
	else if (builtin_code == 4)
		return (pwd());
	else if (builtin_code == 5)
		return (unset(all));
	else if (builtin_code == 6)
		return (env(all));
	return (0);
}

void	ft_free_only_builtin(t_all *all, int status)
{
	ft_free_tab((void **)all->tokens);
	ft_free_tab_size((void **)all->arg, all->args_size + 1);
	dup2(all->default_out_fd, 1);
	safeclose(all->default_out_fd);
	update_status_int(all, status);
}

/*only one builtin no pipe*/
void	only_builtin(t_all *all, int index_pipe, int builtin_code)
{
	int	builtin_fd;

	all->pid[index_pipe] = -1;
	all->default_out_fd = dup(1);
	tokens_positif(all->tokens, 1);
	builtin_fd = get_outfile_infile_builtin2(all, all->tokens);
	if (builtin_fd == -3)
	{
		all->status = 1;
		return ((void)ft_free_only_builtin(all, 1));
	}
	if (builtin_fd == -2)
	{
		free_redir_list(all);
		all->status = 1;
		return ((void)ft_free_only_builtin(all, 1));
	}
	all->tokens = kick_empty_tokens(all->tokens);
	tokens_positif(all->tokens, 0);
	all->status = execute_builtin(all, builtin_code);
	ft_free_only_builtin(all, all->status);
}
