/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:28:12 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/22 00:16:52 by lboulang         ###   ########.fr       */
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
void	execute_builtin(char **tokens, t_all *all, int i, char **all_lines)
{
	if (i == 0)
		cd();
	else if (i == 1)
		echo(tokens);
	else if (i == 2)
		ft_exit(all, tokens, all_lines);
	else if (i == 3)
		export(all, tokens, 1);
	else if (i == 4)
		pwd();
	else if (i == 5)
		unset(all->env, tokens);
	else if (i == 6)
		env(all);
}
