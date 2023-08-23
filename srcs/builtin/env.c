/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:37:46 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/23 20:56:22 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env(t_all *all)//faut parser sale fdp emv $? ca maerche pas
{
	t_env *tmp;

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