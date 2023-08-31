/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:48:34 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 12:56:14 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_putain(char *cmd, t_env *env)
{
	char	*varpath;
	char	**spl_path;
	char	*cmd_path;

	varpath = get_key(env, "PATH");
	if (!varpath)
	{
		cmd_path = ft_check_acces(NULL, cmd, -1);
		return (cmd_path);
	}
	spl_path = ft_split(varpath, ':');
	free(varpath);
	cmd_path = ft_check_acces(spl_path, cmd, -1);
	return (ft_free_tab((void **)spl_path), cmd_path);
}

void	ft_free_child(t_all *all, char **env_array, char *cmd_path, int status)
{
	free_t_env(&all->env);
	ft_free_tab((void **)env_array);
	ft_free_tab((void **)all->tokens);
	ft_free_tab((void **)all->all_lines);
	if (cmd_path)
		free(cmd_path);
	ft_free_tab_size((void **)all->arg, all->args_size + 1);
	free_redir_list(all);
	exit(status);
}

void	child(t_all *all, int index_pipe, int builtin_code)
{
	char	*cmd_path;
	char	**env;

	signal(SIGINT, &ctrlc);
	tokens_positif(all->tokens, 1);
	redirection_execve(all, all->all_lines, index_pipe);
	get_outfile_infile(all, all->tokens);
	if (!all->cmd)
		ft_free_child(all, NULL, NULL, 1);
	all->tokens = kick_empty_tokens(all->tokens);
	if (builtin_code >= 0)
	{
		tokens_positif(all->tokens, 0);
		all->status = execute_builtin(all, builtin_code);
		ft_free_child(all, NULL, NULL, all->status);
	}
	cmd_path = get_path_putain(all->cmd, all->env);
	env = get_env(all->env);
	if (cmd_path && all->cmd)
	{
		tokens_positif(all->tokens, 0);
		execve(cmd_path, all->tokens, env);
	}
	ft_free_child(all, env, cmd_path, 127);
}

void	redirection_execve(t_all *all, char **all_lines, int index_pipe)
{
	if (index_pipe != 0)
	{
		dup2(all->prev_fd, 0);
		safeclose(all->prev_fd);
	}
	if (index_pipe != ft_tab_len(all_lines) - 1)
	{
		dup2(all->link_fd[1], 1);
	}
	safeclose(all->link_fd[0]);
	safeclose(all->link_fd[1]);
}
