/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:37:46 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/27 18:20:48 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
env sans options ni arguments;
*/
int	env(t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	if (!tmp)
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (tmp->display == 1)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
