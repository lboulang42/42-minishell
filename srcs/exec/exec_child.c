/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:48:34 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 03:04:34 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path_putain(char *cmd, t_env *env)
{
	char *PATH;
	char **spl_path;
	char *cmd_path;
	PATH = get_key(env, "PATH");
	if (!PATH)
	{
		cmd_path = ft_check_acces(NULL, cmd, -1);
		return (cmd_path);	
	}
	spl_path = ft_split(PATH, ':');//ca ca merde
	free(PATH);
	cmd_path = ft_check_acces(spl_path, cmd, -1);
	ft_free_tab((void **)spl_path);
	return (cmd_path);
}


void ft_free_child(t_all *all, char **env_array, char *cmd_path)
{
	free_t_env(&all->env);
	ft_free_tab((void **)env_array);
	ft_free_tab((void **)all->tokens);
	ft_free_tab((void **)all->all_lines);
	if (cmd_path)
		free(cmd_path);
	// free_redir_list(all);
}


void child(t_all *all, int index_pipe, int builtin_code)
{
	char	*cmd_path;
	char	**env;

	// fprintf(stderr, "chec3\n");
	signal(SIGINT, & ctrlc);
	tokens_positif(all->tokens, 1);
	redirection_execve(all, all->all_lines, index_pipe);
	get_outfile_infile(all, all->tokens, all->all_lines, index_pipe);
	// fprintf(stderr, "chec4\n");
	fprintf(stderr, "all->cmd = %s\n", all->cmd);
	
	if (!all->cmd)
	{
		ft_free_child(all, NULL, NULL);
		ft_free_tab_size((void **)all->arg, all->args_size+1);
		free_redir_list(all);
		exit(1);
	}
	all->tokens = kick_empty_tokens(all->tokens);
		// fprintf(stderr, "chec5\n");
	if (builtin_code >= 0)
	{
		tokens_positif(all->tokens, 0);
		all->status = execute_builtin(all, builtin_code);
		free_t_env(&all->env);
		ft_free_tab((void **)all->tokens);
		ft_free_tab((void **)all->all_lines);
		ft_free_tab_size((void **)all->arg, all->args_size+1);
		free_redir_list(all);
		exit(all->status);
	}
	cmd_path = get_path_putain(all->cmd, all->env);
	env = get_env(all->env);
	// fprintf(stderr, "chec6\n");
	if (cmd_path && all->cmd)
	{
		tokens_positif(all->tokens, 0);
		execve(cmd_path, all->tokens, env);
	}
	// fprintf(stderr, "sors ici\n");
	// ft_free_tab((void **)all->tokens);
	ft_free_child(all, env, cmd_path);
	ft_free_tab_size((void **)all->arg, all->args_size+1);
	free_redir_list(all);
	exit(127);
}

void redirection_execve(t_all *all, char **all_lines, int index_pipe)
{
	if (index_pipe != 0)
	{
		dup2(all->prev, 0);
		safeclose(all->prev);
	}
	if (index_pipe != ft_tab_len(all_lines) - 1)
	{
		dup2(all->link_fd[1], 1);
	}
	safeclose(all->link_fd[0]);
	safeclose(all->link_fd[1]);
}
