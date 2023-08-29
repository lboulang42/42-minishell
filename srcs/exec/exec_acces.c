/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_acces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:51:14 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/29 19:45:47 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*ft_access_fail renvoie un message d'erreur similaire a celui de bash dans le cas ou la commande ne peut pas être executée*/
/*
En cas d'erreur access return -1;
Si F_OK fail :
	-Ne peut pas accéder au fichier parcequ'il n'existe pas.
	- si '/' dans le nom du fichier : No such file or directory
	- si pas de '/' dans le nom du fichier : command not found;
	- Error code : 127 (sera set par défaut dans ft_child());
Si X_OK fail :
	- Ne peut pas accéder au fichier (plusieurs raisons différentes, on set l'error code avec strerror)
	- Error code : 126 (via ft_kill_dir)
*/
void	ft_access_fail(char **PATHvaaaar, char *cmd_path, char *cmd_name)
{
	char *tmp;

	if (cmd_path)
	{
		if (access(cmd_path, F_OK))
		{
			if (!ft_strchr(cmd_name, '/'))
				fprintf(stderr, "1%s :%s : %s\n", MINI, cmd_name, ERR_CMD);
			else
				fprintf(stderr, "2%s :%s : %s\n", MINI, cmd_name, ERR_NOSUCHF);
		}
		else if (access(cmd_path, X_OK))
		{
			fprintf(stderr, "3%s : %s: %s\n", MINI, cmd_name,  strerror(errno));
			ft_kill_dir(PATHvaaaar, cmd_path, cmd_name);
		}
	}
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
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
            if (file_is_directory(cmd_path, cmd_name))
                ft_kill_dir(env_path, cmd_path, cmd_name);
			return (cmd_path);
		}
		return (ft_access_fail(env_path, cmd_path, cmd_name), NULL);
	}
	while (env_path && env_path[++i])
	{
		cmd_path = ft_join_path(env_path[i], cmd_name);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
            if (file_is_directory(cmd_path, cmd_name))
                ft_kill_dir(env_path, cmd_path, cmd_name);
			return (cmd_path);
		}
		if (env_path[i + 1])
			free(cmd_path);
	}
	return (ft_access_fail(env_path, cmd_path, cmd_name), NULL);
}
