/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:19:10 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/02 20:34:00 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_acces(char *path, char *cmd_name)
{
	if (path[ft_strlen(path) - 1] == '/')
		return ((void)ft_printf("Pipex : %s: not a directory\n", cmd_name));
	if (access(path, F_OK))
		return ((void)ft_printf("Pipex : command not found: %s\n", cmd_name));
	if (access(path, X_OK))
		return ((void)ft_printf("Pipex : permission denied : %s\n", cmd_name));
}

char	*generate_test_path(char *path, char *cmd)
{
	char	*join_tmp;
	char	*test_path;

	join_tmp = ft_strjoin(path, "/");
	if (!join_tmp)
		return (NULL);
	test_path = ft_strjoin(join_tmp, cmd);
	free(join_tmp);
	if (!test_path)
		return (NULL);
	return (test_path);
}

char	*check_relative_paths_2(char **path, char *cmd_name)
{
	int		i;
	char	*test_path;

	i = -1;
	if (!*cmd_name)
		return (NULL);
	while (path[++i])
	{
		test_path = generate_test_path(path[i], cmd_name);
		if (!test_path)
			return (NULL);
		if (!access(test_path, F_OK | X_OK))
			return (test_path);
		if (path[i + 1])
			free(test_path);
		else
		{
			ft_check_acces(test_path, cmd_name);
			free(test_path);
		}
	}
	return (NULL);
}


char	**keep_path_2(t_env *env)
{
    t_env   *tmp_env;

    
	int		i;
	char	**tmp;
	char	**path;

	i = -1;
    while (tmp_env)
    {
        if (!ft_strncmp("PATH=", tmp_env->name, 5))
		{
			path = ft_split(tmp_env->value, ':');
			if (!path)
				return (NULL);
			return (path);
		}
        tmp_env = tmp_env->next;
    }
	return (NULL);
}


char	*find_cmd_2(t_all *all, char *cmd_name)
{
	char	*result;
    char    **path;
	if (!*cmd_name)
		return (NULL);
	if (ft_strrchr(cmd_name, '/'))
	{
		if (!access(cmd_name, F_OK | X_OK))
			return (cmd_name);
		return (ft_check_acces(cmd_name, cmd_name), NULL);
	}
	path = keep_path_2(all->env);
	result = check_relative_paths_2(path, cmd_name);
	ft_free_tab((void **)path);
	return (result);
}
