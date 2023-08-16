/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/16 19:00:08 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_all	all;

	(void)argv;
	if (argc != 1)
		return (0);
	init_env(&all, env);
	init_shell(&all, env);
	run_easyshell(&all, env);
	free_t_env(&all.env);
	return (0); // return last status code
}

void run_easyshell(t_all *all, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("easy-shell> ");
		if (!input)
			break;
		if (!*input)
		{
			free(input);
			continue;
		}
		add_history(input);
		inverse_string(input, SQUOTE);	 // inverse les squote
		input = add_spaces_input(input); // gab function
		input = expand_string(input, all->env);
		inverse_string(input, DQUOTE); // inverse aussi les dquote pour l'exec (seront remis nrmal apres)
		exec_init(all, input);
		free(input);
	}
}
