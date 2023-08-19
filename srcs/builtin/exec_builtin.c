/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:28:12 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/19 16:38:24 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	static char *bltnnames[7] = {"cd", "echo", "exit", "export", "pwd", "unset", "env"};
	int i;

	i = -1;
	while (++i < 7)
		if (is_same_string(cmd_name, bltnnames[i]))
			return (i);
	return (-1);
}

int exec_builtin(char **tokens, t_all *all, int i, char **all_lines, int index_pipe)
{
	int signal;

	if (i == 0)
		signal = cd();
	if (i == 1)
		signal = echo();
	if (i == 2)
		signal = ft_exit();
	if (i == 3)
		signal = export();
	if (i == 4)
		signal = pwd();
	if (i == 5)
		signal = unset();
	if (i == 6)
		signal = env(all);
	//update_signal;
	return (signal);
}