/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:27:33 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 02:59:29 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_t_env(t_env *env)//tempo
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		printf("entry in env :\nName : %s\nValue : %s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}


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
	if(!*env)
	{
		*env = new;
		return ;
	}
	temp = get_last_t_env(*env);
	temp->next = new;
}

char    *get_key(t_env *full_env, char *key)
{
    t_env   *tmp;

    tmp = full_env;
    if (!key)
		return (NULL);
    while (tmp)
    {
        if (is_same_string(tmp->name, key))
            return (ft_strdup(tmp->value));
        tmp = tmp->next;
    }
	return ( NULL);//faudra kick plus tarderr_msg(ERR_KEY_VAL, "get_key()"),
}