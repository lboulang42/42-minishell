/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:21:15 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 17:54:04 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *env_line)
{
	char	*env_name;
	char	**env_split;

	if (!env_line)
		return (NULL);
	env_split = ft_split(env_line, '=');
	if (!env_split)
		return (err_msg(ERR_MALL, "get_env_name() ftsplit()"), NULL);
	env_name = ft_strdup(env_split[0]);
	ft_free_tab((void **)env_split);
	if (!env_name)
		return (err_msg(ERR_MALL, "get_env_name() ftstrdup()"), NULL);
	return (env_name);
}

char	*get_env_value(char *env_line, char *name)
{
	char	*value;

	value = ft_substr(env_line, ft_strlen(name) + 1, ft_strlen(env_line));
	if (!value)
		return (err_msg(ERR_MALL, "get_env_value() ft_substr()"), NULL);
	return (value);
}

void	init_env(t_all *data, char **env)
{
	int		i;
	char	*value;
	char	*name;

	i = -1;
	if (!env || !*env)
	{
		add_t_env(&data->env, "?", "0", 0);
		return ;
	}
	while (env[++i])
	{
		name = get_env_name(env[i]);
		if (name)
		{
			value = get_env_value(env[i], name);
			if (value)
			{
				add_t_env(&data->env, name, value, 1);
				free(value);
			}
			free(name);
		}
	}
	add_t_env(&data->env, "?", "0", 0);
}

void	free_t_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->name)
			free((*env)->name);
		if ((*env)->value)
			free((*env)->value);
		free((*env));
		*env = tmp;
	}
}

t_env	*t_env_new(char *name, char *value, int display)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (err_msg(ERR_MALL, "t_env_new()"), NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->display = display;
	new->next = NULL;
	return (new);
}
