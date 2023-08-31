/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_acces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:51:14 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:01:49 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_kill_dir(char **PATHvar, char *cmd_path)
{
	t_all	*all;

	all = init_data();
	if (cmd_path)
		free(cmd_path);
	ft_free_tab((void **)all->tokens);
	free_t_env(&all->env);
	ft_free_tab((void **)PATHvar);
	ft_free_tab((void **)all->all_lines);
	ft_free_tab_size((void **)all->arg, all->args_size + 1);
	free_redir_list(all);
	exit(126);
}

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

/*
En cas d'erreur access return (-1);
Si F_OK fail :
	-Ne peut pas accéder au fichier parcequ'il n'existe pas.
	- si '/' dans le nom du fichier : No such file or directory
	- si pas de '/' dans le nom du fichier : command not found;
	- Error code : 127 (sera set par défaut dans ft_child());
Si X_OK fail :
	- Ne peut pas accéder au fichier (plusieurs raisons différentes, on set 
		l'error code avec strerror)
	- Error code : 126 (via ft_kill_dir)
*/
void	ft_access_fail(char **PATHvaaaar, char *cmd_path, char *cmd_name)
{
	if (cmd_path)
	{
		if (access(cmd_path, F_OK))
		{
			if (!ft_strchr(cmd_name, '/'))
				ft_printf("%s :%s : %s\n", MINI, cmd_name, ERR_CMD);
			else
				ft_printf("%s :%s : %s\n", MINI, cmd_name, ERR_NOSUCHF);
		}
		else if (access(cmd_path, X_OK))
		{
			ft_printf("%s : %s: %s\n", MINI, cmd_name, strerror(errno));
			ft_kill_dir(PATHvaaaar, cmd_path);
		}
	}
	else
		ft_printf("%s :%s : %s\n", MINI, cmd_name, ERR_CMD);
	if (cmd_path)
		free(cmd_path);
}

/*
separate way if cmd is global path / only name / only name without PATH in env
*/
char	*ft_check_acces(char **env_path, char *cmd_name, int i)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (ft_strchr(cmd_name, '/'))
	{
		cmd_path = ft_strdup(cmd_name);
		if (access(cmd_path, F_OK | X_OK) != -1 && isdir(cmd_path, cmd_name))
			ft_kill_dir(env_path, cmd_path);
		if (access(cmd_path, F_OK | X_OK) != -1)
			return (cmd_path);
		return (ft_access_fail(env_path, cmd_path, cmd_name), NULL);
	}
	while (env_path && env_path[++i])
	{
		cmd_path = ft_join_path(env_path[i], cmd_name);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			if (isdir(cmd_path, cmd_name))
				ft_kill_dir(env_path, cmd_path);
			return (cmd_path);
		}
		if (env_path[i + 1])
			free(cmd_path);
	}
	return (ft_access_fail(env_path, cmd_path, cmd_name), NULL);
}
