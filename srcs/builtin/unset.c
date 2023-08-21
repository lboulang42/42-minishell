/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/22 00:08:17 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void do_unset(t_env *env, char *key)
{
    t_env *tmp;
    t_env *tmp2;
    
    tmp = env;
    tmp2 = env;
    while (tmp)
    {
        if (is_same_string(tmp->name, key))
        {
            if (tmp->next)
                tmp2->next = tmp->next;
            else
                tmp2->next = NULL;
            if (tmp->name)
                free(tmp->name);
            if (tmp->value)
                free(tmp->value);
            free(tmp);
            return ;
        }
        tmp2 = tmp;
        tmp = tmp->next;
    }
}

void    unset(t_env *env, char **tokens)
{
    int i;

    i = 0;
    while (tokens[++i])
    {
        if (is_same_string(tokens[i], "?"))
            continue;
        do_unset(env, tokens[i]);
    }
}