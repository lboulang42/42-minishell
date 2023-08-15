/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:18:56 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/02 20:33:34 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**keep_path(t_all *all)
{
	int		i;
	char	**tmp;
	char	**path;

	i = -1;
	while (all->env[++i])
	{
		if (!ft_strncmp("PATH=", all->env[i], 5))
		{
			tmp = ft_split(all->env[i], '=');
			if (!tmp)
				return (NULL);
			path = ft_split(tmp[1], ':');
			if (!path)
				return (free_split(tmp), NULL);
			free_split(tmp);
			return (path);
		}
	}
	return (NULL);
}



char	*check_absolute_path(char **cmd_split)
{
	if (!cmd_split[0])
		return (NULL);
	if (ft_strrchr(cmd_split[0], '/'))
	{
		if (!access(cmd_split[0], F_OK | X_OK))
			return (cmd_split[0]);
		else
			ft_check_acces(cmd_split[0], cmd_split[0]);
	}
	return (NULL);
}


char	*check_relative_paths(t_all *all, char **cmd_split)
{
	int		i;
	char	*test_path;

	i = -1;
	if (!*cmd_split)
		return (NULL);
	while (all->path[++i])
	{
		test_path = generate_test_path(all->path[i], cmd_split[0]);
		if (!test_path)
			return (NULL);
		if (!access(test_path, F_OK | X_OK))
			return (test_path);
		if (all->path[i + 1])
			free(test_path);
		else
		{
			ft_check_acces(test_path, cmd_split[0]);
			free(test_path);
		}
	}
	return (NULL);
}
