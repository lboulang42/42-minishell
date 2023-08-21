/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:25:53 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/21 17:30:31 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void    export(t_all *all, char **tokens)
{
	int i;
	int index_egal;
	char *name;
	char *value;
	
	i = 0;
	if (!tokens[1])
		return ((void)print_export(all));
	while (tokens[++i])
	{
		if (ft_strchr(tokens[i], '='))
		{
			name = get_env_name(tokens[i]);
			value = get_env_value(tokens[i], name);
			do_export(all, name, value);
			free(name);
			free(value);
		}
	}
}


*/
int    unset(void)
{
    fprintf(stderr, "unset() triggered\n");
    return (6);
}