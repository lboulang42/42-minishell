/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/30 17:47:30 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_unset(t_all *all, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = all->env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				all->env = tmp->next;
			free(tmp->name);
			if (tmp->value)
				free(tmp->value);
			tmp->name = NULL;
			tmp->value = NULL;
			tmp->display = 0;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset(t_all *all)
{
	int	i;

	i = 0;
	if (!all->tokens[1])
		return (0);
	while (all->tokens[++i])
	{
		if (!is_same_string(all->tokens[i], "?"))
			do_unset(all, all->tokens[i]);
	}
	return (0);
}
