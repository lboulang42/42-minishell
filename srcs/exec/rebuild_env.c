/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:50:03 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/31 12:56:30 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_size(t_env *env)
{
	t_env	*tmp;
	int		counter;

	counter = 0;
	tmp = env;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

/*Return char ** as env from t_env *env */
char	**get_env(t_env *env)
{
	t_env	*tmp;
	char	**res;
	char	*temp2;
	int		counter;

	counter = get_env_size(env);
	res = malloc(sizeof(char *) * (counter + 1));
	if (!res)
		return (NULL);
	tmp = env;
	counter = 0;
	while (tmp)
	{
		temp2 = ft_strjoin(tmp->name, (char *)"=");
		res[counter] = ft_strjoin(temp2, tmp->value);
		free(temp2);
		tmp = tmp->next;
		counter++;
	}
	res[counter] = NULL;
	return (res);
}
