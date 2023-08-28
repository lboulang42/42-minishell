/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:28:12 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/28 11:55:01 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	int			i;
	static char	*bltnnames[7] = {
		"cd", "echo", "exit", "export", "pwd", "unset", "env"
	};

	i = -1;
	while (++i < 7)
		if (is_same_string(cmd_name, bltnnames[i]))
			return (i);
	return (-1);
}

/*
execute le bon builtin
*/
int	execute_builtin(t_all *all, int builtin_code)
{
	if (builtin_code == 0)
		return (cd(all, all->tokens));
	else if (builtin_code == 1)
		return (echo(all->tokens));
	else if (builtin_code == 2)
		return (ft_exit(all), 1);
	else if (builtin_code == 3)
		return (export(all));
	else if (builtin_code == 4)
		return (pwd());
	else if (builtin_code == 5)
		return (unset(all));
	else if (builtin_code == 6)
		return (env(all));
	return (0);
}
