/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:48:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/08/23 18:50:21 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_all *init_data(void)
{
	static t_all data = {0};
	
	return (&data);
}

int main(int argc, char **argv, char **env)
{
	t_all	*all;

	(void)argv;
	if (argc != 1)
		return (1);//EXIT)FAILURE
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	all = init_data();
	init_env(all, env);
	init_shell(all, env);
	run_easyshell(all, env);
	free_t_env(&all->env);
	return (0); // return last status code
}

void	run_easyshell(t_all *all, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("easy-shell> ");
		// signal(SIGINT, & ctrlc);
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		inverse_string(input, SQUOTE);
		inverse_string(input, DQUOTE);
		input = add_spaces_input(input);
		if (syntax_error(all, input) == 1)
		{
			free(input);
			continue ;
		}
		inverse_string(input, DQUOTE);
		input = expand_string(input, all->env);
		inverse_string(input, DQUOTE);
		input = delete_quote(input);
		inverse_string(input, DQUOTE);
		exec_init(all, input);
	}
}
