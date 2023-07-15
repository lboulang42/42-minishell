/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/15 19:46:04 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	static t_all	all;

	(void)argv;
	if (argc != 1)
		return (0);
    init_shell(&all, env);
	run_easyshell(&all, env);
	return (0);
}

void init_shell(t_all *all, char **env)
{
 // add sinal later;   
}

void	run_easyshell(t_all *all, char **env)
{
	char	*str;

	all->env = env;
	while (1)
	{
		str = readline("easy-shell> ");
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		printf("[%s]\n", str);
		add_history(str);
		all->tab = ft_split(str, '|');
		all->nbcmd = counter(str, '|');
		pipex(all, all->tab);
		close_pipes(all);
		free_resources(all);
		free(str);
	}
}
