/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:27:33 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 16:10:40 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_last_t_env(t_env *env)
{
	if (!env)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_t_env(t_env **env, char *name, char *value, int display)
{
	t_env	*temp;
	t_env	*new;

	new = t_env_new(name, value, display);
	if (!env)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	temp = get_last_t_env(*env);
	temp->next = new;
}

char	*get_key(t_env *full_env, char *key)
{
	t_env	*tmp;

	tmp = full_env;
	if (!key)
		return (NULL);
	while (tmp)
	{
		if (is_same_string(tmp->name, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_value_by_key(t_env *full_env, char *key)
{
	t_env	*tmp;

	tmp = full_env;
	if (!key)
		return (NULL);
	while (tmp)
	{
		if (is_same_string(tmp->name, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
