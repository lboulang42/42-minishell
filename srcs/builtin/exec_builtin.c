/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:28:12 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/26 03:02:26 by gcozigon         ###   ########.fr       */
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
int	execute_builtin(char **tokens, t_all *all, int i, char **all_lines)
{
	if (i == 0)
		return (cd(all, tokens));
	else if (i == 1)
		return (echo(tokens));
	else if (i == 2)
		return (ft_exit(all, tokens, all_lines), 1);
	else if (i == 3)
		return (export(all, tokens));
	else if (i == 4)
		return (pwd());
	else if (i == 5)
		return (unset(all, tokens));
	else if (i == 6)
		return (env(all));
	return (0);
}
